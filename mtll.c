#include "mtll.h"
#include "helpers.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_SIZE (128)

// Frees the memory allocated for a list.
// Parameters: head - pointer to the node to be freed
// Free memory allocated for a list.
void mtll_free(node *head)
{
    node *current = head->next;

    // Free data of head node.
    free(head->data);
    free(head);
    
    // Free data and nodes of subsequent nodes.
    node *temp;
    while (current != NULL)
    {
        temp = current;
        current = current->next;
        free_node(temp);
    }
}


//Frees all dynamically allocated memory in the mega list.
// Parameters: mega_list - pointer to the mega list
void mtll_free_all(node *mega_list)
{
    node *current_mega = mega_list;

    // Iterate through the mega list and free each sublist
    node *temp;
    while (current_mega != NULL)
    {
        temp = current_mega;
        current_mega = current_mega->next;

        // Free the sublist and its nodes
        mtll_free(temp->data);
        free(temp);
    }
}

// Stores data into a node based on its type and returns the type.
// Parameters: mega_list - pointer to the mega list, storage - pointer to the node to store data in,
//             data - string containing the data to be stored
// Returns: type of data stored in the node, or -1 if data could not be stored
int store_data(node *mega_list, node *storage, char *data)
{
    char *end = NULL;
    data[strcspn(data, "\n")] = '\0'; 

    // Handle empty data case.
    if (strncmp(data, "\0", 1) == 0)
    {
        // Allocate empty string.
        char *empty_ptr = malloc(1); 
        if (empty_ptr != NULL)
        {
            *empty_ptr = '\0';
            storage->data = (void *)empty_ptr; 
            return storage->type = STRING;
        }
        return -1; // Allocation failure
    }

    // Convert to integer if possible.
    int int_data = strtol(data, &end, 10); 
    if (*end == '\0')
    {
        // Allocate integer.
        int *int_ptr = malloc(sizeof(int)); 
        if (int_ptr != NULL)
        {
            *int_ptr = int_data;
            storage->data = (void *)int_ptr; 
            return storage->type = INTEGER;
        }
        return -1; // Allocation failure
    }

    // Convert to float if possible.
    float float_data = strtof(data, &end); 
    if (*end == '\0')
    {
        // Allocate float.
        float *float_ptr = malloc(sizeof(float)); 
        if (float_ptr != NULL)
        {
            *float_ptr = float_data;
            storage->data = (void *)float_ptr; 
            return storage->type = FLOAT;
        }
        return -1; // Allocation failure
    }

    // Handle character data.
    if (strlen(data) == 1 && (strncmp(data, "\t", 1) != 0 && isprint(data[0])))
    {
        // Allocate character.
        char *char_ptr = malloc(1); 
        if (char_ptr != NULL)
        {
            *char_ptr = *data;
            storage->data = (void *)char_ptr; 
            if (*data < 127 && *data >= 0)
            {
                return storage->type = CHAR; 
            }
            return storage->type = STRING;
        }
        return -1; // Allocation failure
    }

    // Handle list reference.
    char *str_ptr = malloc(strlen(data) + 1); 
    int list_id;
    node *reference;
    strcpy(str_ptr, data);
    if (str_ptr != NULL)
    {
        if (str_ptr[0] == '{' && str_ptr[strlen(data) - 1] == '}' && sscanf(str_ptr, "{%d}", &list_id) == 1)
        {
            free(str_ptr);
            if (valid_id(mega_list, list_id))
            {
                reference = find_sublist(mega_list, list_id);
                if (reference->type == LIST)
                {
                    storage->data = (void *)reference; 
                    return storage->type = LIST;
                }
            }
            return -1; // Invalid or allocation failure
        }
        else if (strpbrk(data, "{}") != NULL)
        {
            free(str_ptr); 
            return -1; // Invalid data format
        }
        else
        {
            storage->data = (void *)str_ptr; 
            return storage->type = STRING;
        }
    }
    return STRING; 
}

// Views the contents of a sublist in a mega list.
// Parameters: mega_list - pointer to the mega list, list_id - ID of the sublist to view,
//             mode - mode indicating whether to print data or types, mega_size - size of the mega list
void mtll_view(node *mega_list, int list_id, printMode mode, int mega_size)
{
    // Find the sublist corresponding to the given list_id
    node *sublist_branch = find_sublist(mega_list, list_id);
    node *sublist_head = sublist_branch->next;

    // If the sublist with the given index is found
    if (sublist_head != NULL)
    {
        mtll_print_list(sublist_head, mode); // Access the sublist to print its contents
        printf("\n");
    }
}



// Prints a summary of all existing lists in the mega list.
// Parameters: mega_list - pointer to the pointer to the mega list, mega_size - size of the mega list
void mtll_view_all(node **mega_list, int mega_size)
{
    if (*mega_list == NULL)
    {
        printf("Number of lists: 0\n");
        return;
    }

    printf("Number of lists: %d\n", mega_size);

    // Print summary of all existing lists and respective id's
    node *current = *mega_list;
    node *sublist;
    while (current != NULL)
    {
        sublist = current->data;
        if (sublist->type == NEST)
        {
            printf("Nested %d\n", *(int *)(sublist->data));
        }
        else
        {
            printf("List %d\n", *(int *)(sublist->data));
        }
        current = current->next;
    }
}

// Removes a sublist from a mega list.
// Parameters: mega_list - pointer to the pointer to the mega list, list_id - ID of the sublist to remove,
//             mega_size - size of the mega list
// Returns: 1 if the sublist is successfully removed, 0 otherwise
// Remove a sublist from the mega list.
int mtll_remove(node **mega_list, int list_id, int mega_size)
{
    node *current = *mega_list;
    node *target = current;

    // Remove sublist by ID
    if (get_list_id(current) == list_id)
    {
        if (has_reference(*mega_list, list_id) == 0)
            *mega_list = (*mega_list)->next; // Remove linkage to first sublist
        else {
            invalid_command("REMOVE");
            return 0;
        }
    }
    else if (mega_size > 0)
    {
        // Find sublist with requested ID
        while (current != NULL)
        {
            if (get_list_id(current->next) == list_id)
            {
                target = current->next; // Found sublist with requested ID
                break;
            }
            current = current->next;
        }
        if (target != NULL && has_reference(*mega_list, list_id) == 0)
            current->next = target->next; // Remove linkage to deleted sublist from megalist
        else {
            invalid_command("REMOVE");
            return 0;
        }
    }
    else {
        invalid_command("REMOVE");
        return 0;
    }

    // Free memory allocated for the sublist
    mtll_free(target->data);
    free(target);
    printf("List %d has been removed.\n\n", list_id);
    mtll_view_all(mega_list, mega_size - 1);
    return 1;
}

// Creates a new sublist and adds it to the mega list.
// Parameters: mega_list - pointer to the pointer to the mega list, size - size of the new sublist,
//             new_list_id - ID of the new sublist
// Returns: 1 if the new sublist is successfully created and added, 0 otherwise
int mtll_create(node **mega_list, int size, int new_list_id)
{
    // Create head of new list
    node *head = (node *)malloc(sizeof(node));
    if (head == NULL) {
        printf("Memory allocation failed for the head of the new list.\n");
        free(head);
        return 0;
    }

    // Initialize head of the new list
    char *id = malloc(3);
    sprintf(id, "%d", new_list_id);
    store_data(*mega_list, head, id);
    free(id);
    head->type = LIST;
    head->next = NULL;

    // Populate the new list
    node *current = head;
    char input[MAX_INPUT_SIZE + 1];
    dataType type;

    node *new_node = (node *)malloc(sizeof(node));
    if (new_node == NULL) {
        free_node(new_node);
        free_node(head);
        invalid_command("NEW");
        return 0;
    }

    for (int i = 0; i < size; i++) {
        if (fgets(input, sizeof(input), stdin) == NULL) {
            mtll_free(head);
            free(new_node);
            return 0;
        }

        node *new_list_node = (node *)malloc(sizeof(node));

        // Store data into new_list_node
        type = store_data(*mega_list, new_list_node, input);

        // Update type of head if nested list
        if (type == LIST) {
            head->type = NEST;
        } else if (type == -1) {
            free(new_list_node);
            mtll_free(head);
            free(new_node);
            invalid_command("NEW");
            return 0;
        }

        new_list_node->next = NULL;

        current->next = new_list_node;
        current = new_list_node;
    }

    // Initialize the new node
    new_node->data = head; // New megalist node points to head of new list
    new_node->next = NULL;

    // Add new node to mega list
    if (*mega_list == NULL)
        *mega_list = new_node;
    else {
        node *last = *mega_list;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = new_node;
    }
    recap(new_node->data);
    return 1;
}

// Deletes a node from a sublist in a mega list.
// Parameters: mega_list - pointer to the mega list, list_id - ID of the sublist to delete from,
//             index - index of the node to delete, mega_size - size of the mega list
// Returns: void

void mtll_delete(node *mega_list, int list_id, int index, int mega_size)
{
    // Find the sublist corresponding to the given list_id
    node *sublist_branch = find_sublist(mega_list, list_id);
    node *sublist_head = sublist_branch->next;

    // Check if index is out of bounds
    int size;
    size = get_list_size(sublist_head);

    if (index < 0 || index > size)
    {
        if (index > size)
        {
            invalid_command("DELETE");
            return;
        }
        index = size + index;
        if (index < 0)
        {
            invalid_command("DELETE");
            return;
        }
    }

    // Traverse the list to find the node to delete
    node *prev = NULL;
    node *current = sublist_head;
    int i = 0;
    while (current != NULL && i < index)
    {
        prev = current;
        current = current->next;
        i++;
    }

    // If the element to delete is not NULL
    if (current != NULL)
    {
        // Remove linkage to deleted node
        if (prev != NULL)
        {
            prev->next = current->next;
        }
        else
        {
            // If deleting head node, override list head
            sublist_head = current->next;
            sublist_branch->next = sublist_head;
        }
        // Free memory for the node
    }
    else
    {
        invalid_command("DELETE");
        return;
    }
    free_node(current);
    update_nestness(sublist_branch);
    recap(sublist_branch);
}

// Inserts a node into a sublist in a mega list.
// Parameters: mega_list - pointer to the pointer to the mega list, list_id - ID of the sublist to insert into,
//             index - index at which to insert the node, mega_size - size of the mega list, data - data to insert
void mtll_insert(node **mega_list, int list_id, int index, int mega_size, char *data)
{
    // Find the sublist corresponding to the given list_id
    node *sublist_branch = find_sublist(*mega_list, list_id);
    node *sublist_head = sublist_branch->next;

    int size = get_list_size(sublist_head);

    // Check if index is out of bounds
    if (index < 0 || index > size)
    {
        if (index > size)
        {
            invalid_command("INSERT");
            return;
        }
        index = size + index + 1;
        if (index < 0)
        {
            invalid_command("INSERT");
            return;
        }
    }

    // Create a new node
    node *new_node = (node *)malloc(sizeof(node));
    if (new_node == NULL)
    {
        return;
    }
    int type = store_data(*mega_list, new_node, data); // Store data into new_node
    if (type == -1 || (type == LIST && has_reference(*mega_list, list_id)))
    {
        invalid_command("INSERT");
        free(new_node);
        return;
    }

    if (size == 0 || index == 0)
    {
        // If the sublist is empty or inserting at index 0, set the new_node as the sublist head
        new_node->next = sublist_head;
        sublist_head = new_node;
        sublist_branch->next = new_node;
    }
    else
    {
        // If the sublist is not empty or inserting at an index greater than 0
        node *prev = NULL;
        node *current = sublist_head;
        int i = 0;
        while (current != NULL && i < index)
        {
            prev = current;
            current = current->next;
            i++;
        }

        // Update pointers to insert the new node
        if (prev != NULL)
        { // Not inserting at head
            prev->next = new_node;
        }
        else
        { // Inserting at head
            *mega_list = new_node;
        }

        new_node->next = current;
    }

    // If we are inserting a list reference, update head to indicate that is contains a nested list.
    if (new_node->type == LIST)
    {
        find_sublist(*mega_list, list_id)->type = NEST;
    }
    update_nestness(sublist_branch);
    recap(sublist_branch);
}