

#include "mtll.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_SIZE (128)

// Retrieves the ID of a sublist from a mega node.
// Parameters: mega_node - pointer to the mega node containing the sublist
// Returns: ID of the sublist, or -1 if mega_node is NULL or sublist is empty
int get_list_id(node *mega_node)
{
    if (mega_node == NULL)
    {
        return -1; // Failed to allocate
    }
    node *sublist = mega_node->data;

    if (sublist != NULL)
    {
        // Return list id
        return *((int *)(sublist->data));
    }
    else
    {
        return -1; // Return -1 if the sublist is empty
    }
}

// Checks if a given mega list contains a reference to a sublist with a specific ID.
// Parameters: mega_list - pointer to the mega list, list_id - ID of the sublist to search for
// Returns: 1 if a reference is found, 0 otherwise
// Checks if a given mega list contains a reference to a sublist with a specific ID.
// Parameters:
// - mega_list: pointer to the mega list
// - list_id: ID of the sublist to search for
// Returns:
// - 1 if a reference is found, 0 otherwise
int has_reference(node *mega_list, int list_id)
{
    node *i = mega_list;
    node *reference_head;

    // Iterate through Mega_list
    while (i != NULL)
    {
        // Sublist traversal pointer
        node *j = (node *)((node *)i->data)->next;

        // Iterate through sublist
        while (j != NULL)
        {
            // Check if the element is a reference to a sublist
            if (j->type == LIST || j->type == NEST)
            {
                reference_head = j->data;
                // Check if the ID matches the specified list_id
                if (*((int *)(reference_head->data)) == list_id)
                {
                    return 1; // Has reference
                }
            }
            j = j->next; 
        }
        i = i->next; 
    }

    return 0; // No reference
}

// Retrieves the size of a sublist.
// Parameters: head - pointer to the head of the sublist
// Returns: size of the sublist
int get_list_size(node *head)
{
    node *current = head;
    int size = 0;

    // Iterate through sublist
    while (current != NULL)
    {
        size++;
        current = current->next; 
    }

    return size; 
}


// Checks if a mega list contains a sublist with a specific ID.
// Parameters: mega_list - pointer to the mega list, list_id - ID of the sublist to search for
// Returns: 1 if sublist with the given ID exists, 0 otherwise
int valid_id(node *mega_list, int list_id)
{
    if (list_id < 0) // Negative ID, return false
        return 0;

    node *current = mega_list; // Iterate through mega list
    while (current != NULL)
    {
        if (get_list_id(current) == list_id) // Match found, return true
            return 1;
        current = current->next;
    }
    return 0; // No match found, return false
}

// Prints an error message for an invalid command.
// Parameters: command - string representing the invalid command
void invalid_command(char *command)
{
    printf("INVALID COMMAND: %s\n", command);
    return;
}

// Finds and returns a pointer to a sublist with a specific ID.
// Parameters: mega_list - pointer to the mega list, list_id - ID of the sublist to search for
// Returns: pointer to the sublist with the given ID, or NULL if not found
node *find_sublist(node *mega_list, int list_id)
{
    node *current = mega_list;
    while (current != NULL)
    {
        if (get_list_id(current) == list_id)
        {
            current = ((node *)current->data);
            break;
        }
        current = current->next;
    }
    return current;
}

// Updates the type of a sublist to indicate its nestness.
// Parameters: sublist_branch - pointer to the branch node of the sublist
void update_nestness(node *sublist_branch)
{
    node *current = sublist_branch->next;
    while (current != NULL)
    {
        if (current->type == NEST || current->type == LIST)
        {
            sublist_branch->type = NEST;
            return;
        }
        current = current->next;
    }
    sublist_branch->type = LIST;
}

// Stores data into a node based on its type and returns the type.
// Parameters: mega_list - pointer to the mega list, storage - pointer to the node to store data in,
//             data - string containing the data to be stored
// Returns: type of data stored in the node, or -1 if data could not be stored
int store_data(node *mega_list, node *storage, char *data)
{
    char *end = NULL; // Allocating space for a single char
    data[strcspn(data, "\n")] = '\0';

    if (strncmp(data, "\0", 1) == 0)
    {
        char *empty_ptr = malloc(1);
        if (empty_ptr != NULL)
        {
            *empty_ptr = '\0';
            storage->data = (void *)empty_ptr;
            // Freeing allocated memory
            return storage->type = STRING;
        }
        // Freeing allocated memory
        return -1; // Return an error code in case of allocation failure
    }

    int int_data = strtol(data, &end, 10);
    if (*end == '\0')
    {
        int *int_ptr = malloc(sizeof(int));
        if (int_ptr != NULL)
        {
            *int_ptr = int_data;
            storage->data = (void *)int_ptr;
            // Freeing allocated memory
            return storage->type = INTEGER;
        }
        // Freeing allocated memory
        return -1;
    }

    float float_data = strtof(data, &end);
    if (*end == '\0')
    {
        float *float_ptr = malloc(sizeof(float));
        if (float_ptr != NULL)
        {
            *float_ptr = float_data;
            storage->data = (void *)float_ptr;
            // Freeing allocated memory
            return storage->type = FLOAT;
        }
        // Freeing allocated memory
        return -1;
    }

    if (strlen(data) == 1 && (strncmp(data, "\t", 1) != 0 && isprint(data[0])))
    {
        char *char_ptr = malloc(1);
        if (char_ptr != NULL)
        {
            *char_ptr = *data;
            storage->data = (void *)char_ptr;
            if (*data < 127 && *data >= 0)
            {
                // Freeing allocated memory
                return storage->type = CHAR;
            }
            // Freeing allocated memory
            return storage->type = STRING;
        }
        else
        {
            // Freeing allocated memory
            return -1;
        }
    }

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
                    // Freeing allocated memory
                    return storage->type = LIST;
                }
            }
            // Freeing allocated memory
            return -1;
        }
        else if (strpbrk(data, "{}") != NULL)
        {
            free(str_ptr); // Freeing allocated memory
                           // Freeing allocated memory
            return -1;
        }
        else
        {
            storage->data = (void *)str_ptr;
            // Freeing allocated memory
            return storage->type = STRING;
        }
    }
    // Freeing allocated memory
    return STRING;
}

// Frees the memory allocated for a node.
// Parameters: Node - pointer to the node to be freed
void free_node(node *Node)
{ // Free dynamically allocated memory of node and attributes.
    if (Node->data != NULL && Node->type != LIST)
    {
        free(Node->data);
    }

    free(Node);
    return;
}

// Frees the memory allocated for a list.
// Parameters: head - pointer to the node to be freed
void mtll_free(node *head)
{ 

    node *current = head->next;
    free(head->data);
    free(head);
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
    node *temp;
    while (current_mega != NULL)
    {
        temp = current_mega;
        current_mega = current_mega->next;
        mtll_free(temp->data);
        free(temp);
    }
}


// Prints the contents of a node.
// Parameters: element - pointer to the node
void print_node(node *element)
{
    node *sublist;

    switch (element->type)
    {

    case LIST:
        sublist = (node *)element->data;
        printf("{List %d}", *(int *)(sublist->data));
        break;

    case NEST:
        sublist = (node *)element->data;
        printf("{List %d}", *(int *)(sublist->data));
        break;

    case INTEGER:
        printf("%d", *(int *)element->data);
        break;

    case FLOAT:
        printf("%.2f", *(float *)element->data);
        break;

    case CHAR:
        printf("%c", *(char *)element->data);
        break;

    case STRING:
        printf("%s", (char *)element->data);
        break;

    default:
        printf("ERROR: TYPE UNKOWN");
        break;
    }
}

// Prints the type of a node.
// Parameters: node - pointer to the node
void print_node_type(node *node)
{

    switch (node->type)
    {

    case NEST:
        printf("reference");
        break;

    case LIST:
        printf("reference");
        break;

    case INTEGER:
        printf("int");
        break;

    case FLOAT:
        printf("float");
        break;

    case CHAR:
        printf("char");
        break;

    case STRING:
        printf("string");
        break;

    default:
        printf("ERROR: TYPE UNKOWN");
        break;
    }
    return;
}

// Prints the contents or types of nodes in a list based on the specified mode.
// Parameters: head - pointer to the head of the list, mode - mode indicating whether to print data or types
void mtll_print_list(node *head, printMode mode)
{
    node *current = head;

    // For each node, print either types, contents, or contents inc sublist depending on mode.
    while (current != NULL)
    {
        if (mode == DATA)
        {
            print_node(current);
        }
        else if (mode == TYPE)
        {
            print_node_type(current);
        }
        else if (mode == NESTED)
        {
            if (current->type != LIST && current->type != NEST)
            {
                print_node(current);
            }
            else
            { // Print contents of nested node.
                printf("{");
                mtll_print_list((node *)(((node *)current->data)->next), DATA);
                printf("}");
            }
        }
        if (current->next != NULL)
        {
            printf(" -> ");
        }
        current = current->next;
    }
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
    else
    {
        printf("Sublist with ID %d not found.\n", list_id);
    }
}

// Prints the list number and contents.
// Parameters: sublist_branmch - pointer to the sublist to print
void recap(node *sublist_branch)
{
    // Recap of list contents after manipulations.
    node *sublist_head = sublist_branch->next;
    if (sublist_branch->type == NEST)
    {
        printf("Nested %d: ", *(int *)(sublist_branch->data));
    }
    else
    {
        printf("List %d: ", *(int *)(sublist_branch->data));
    }
    mtll_print_list(sublist_head, DATA);
    printf("\n");
    return;
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
int mtll_remove(node **mega_list, int list_id, int mega_size)
{
    node *current = *mega_list;
    node *target = current;

    if (get_list_id(current) == list_id)
    {
        if (has_reference(*mega_list, list_id) == 0)
        {
            *mega_list = (*mega_list)->next; // Remove linkage to first sublist
        }
        else
        {
            invalid_command("REMOVE");
            return 0;
        }
    }
    else if (mega_size > 0)
    {
        // Search for requested id
        while (current != NULL)
        {
            if (get_list_id(current->next) == list_id)
            {
                target = current->next; // Found the sublist with requested id
                break;
            }
            current = current->next;
        }
        if (target != NULL && has_reference(*mega_list, list_id) == 0)
        {                                 // If the sublist exists
            current->next = target->next; // Remove linkage to deleted sublist from megalist
        }
        else
        {
            invalid_command("REMOVE");
            return 0;
        }
    }
    else
    {
        invalid_command("REMOVE");
        return 0;
    }
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

    // Head of new list
    node *head = (node *)malloc(sizeof(node));
    if (head == NULL)
    {
        printf("Memory allocation failed for the head of the new list.\n");
        free(head);
        return 0;
    }

    // Initialize the head of the new list
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
    if (new_node == NULL)
    {
        free_node(new_node);
        free_node(head);
        invalid_command("NEW");
        return 0;
    }

    for (int i = 0; i < size; i++)
    {
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            mtll_free(head);
            free(new_node);
            return 0;
        }

        node *new_list_node = (node *)malloc(sizeof(node));

        type = store_data(*mega_list, new_list_node, input);

        if (type == LIST)
        {
            head->type = NEST;
        }
        else if (type == -1)
        {
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

    if (*mega_list == NULL)
    { // If megalist is empty, initialize first element
        *mega_list = new_node;
    }
    else
    {
        node *last = *mega_list; // If megalist is not empty, find the last index and add a new node
        while (last->next != NULL)
        {
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
// Returns: void
void mtll_insert(node **mega_list, int list_id, int index, int mega_size, char *data)
{
    // Find the sublist corresponding to the given list_id
    node *sublist_branch = find_sublist(*mega_list, list_id);
    node *sublist_head = sublist_branch->next;

    int size = get_list_size(sublist_head);

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