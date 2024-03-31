#include "mtll.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_INPUT_SIZE (128)
#define ERROR (0)

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
invalid_command(char* command)
{
    printf("INVALID COMMAND: %s", command);
}

void print_node(node* node){
    if (node == NULL){
        prtinf('ERROR: NODE NOT FOUND');
=======
int get_list_id(node* sublist) {
=======
int get_list_id(node* mega_node) {
    node* sublist = mega_node->data;
>>>>>>> 1505f78 (Added: mtll_insert Fixed: mtll_view, delete)
    if (sublist != NULL) {
        return *((int*)(sublist->data));
    }else {
<<<<<<< HEAD
        // Handle error: sublist or sublist->data is NULL
        return -1; // Return a default value to indicate failure
=======
        return -1; 
=======
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
>>>>>>> 7005796 (Implemented Testcases, Completed Documentation.)
>>>>>>> b5e4d69 (Testcases, Documentation, Refactoring, and Finalizing)
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

<<<<<<< HEAD
int valid_id(node* mega_list, int list_id){
    if(list_id < 1){
=======
// Checks if a mega list contains a sublist with a specific ID.
// Parameters: mega_list - pointer to the mega list, list_id - ID of the sublist to search for
// Returns: 1 if sublist with the given ID exists, 0 otherwise
int valid_id(node *mega_list, int list_id)
{
    if (list_id < 0) // Negative ID, return false
>>>>>>> 7005796 (Implemented Testcases, Completed Documentation.)
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

<<<<<<< HEAD
node* element_from_index(node *list, int index, int list_size) {
    if (list == NULL) {
        return NULL; // Return NULL if the list is empty
    }
    
    if (list->type == LIST) { // If input is a mega_list node
        int i = 0;
        node *current = list;
        while (current != NULL) {
            if (get_list_id(current) == index) {
                return current->data; // Return the sublist stored in the mega_list node
            }
            current = current->next;
        }
    } else if (index >= 0 && index < list_size) { // If input is a regular list node and index is valid
        int i = 0;
        node *current = list;
        while (i < index && current != NULL) {
            current = current->next;
            i++;
        }
        return current;
    }
    return NULL; // Return NULL if the index is out of bounds or the list type is unknown
}

<<<<<<< HEAD


void store_data(node* storage, char *data) {
=======
=======
<<<<<<< HEAD
node* find_sublist(node* mega_list, int list_id){
    node *current = mega_list;
    while (current != NULL) {
        if (get_list_id(current) == list_id) {
            current = ((node*)current->data);
            break;
        }
=======
// Finds and returns a pointer to a sublist with a specific ID.
// Parameters: mega_list - pointer to the mega list, list_id - ID of the sublist to search for
// Returns: pointer to the sublist with the given ID, or NULL if not found
node *find_sublist(node *mega_list, int list_id)
{
    node *current = mega_list;

    // Search for sublist with ID.
    while (current != NULL)
    {
        // Return sublist if found.
        if (get_list_id(current) == list_id)
            return ((node *)current->data);

>>>>>>> 7005796 (Implemented Testcases, Completed Documentation.)
        current = current->next;
    }
    // Return NULL if not found.
    return NULL;
}

<<<<<<< HEAD
>>>>>>> b5e4d69 (Testcases, Documentation, Refactoring, and Finalizing)
<<<<<<< HEAD
dataType store_data(node* mega_list, node* storage, char *data) {
>>>>>>> 7560cf6 (Refined Input Handling, Bug Fixes, and Enhanced Error Handling)
    char *end;
<<<<<<< HEAD
=======
    long int int_data;
    float float_data;
>>>>>>> e7594d1 (Error handling and memory leaks)
=======
void update_nestness(node* sublist_branch){
    node* current = sublist_branch->next;
    while (current != NULL){
        if (current->type == NEST || current->type == LIST){
=======
// Updates the type of a sublist to indicate its nestness.
// Parameters: sublist_branch - pointer to the branch node of the sublist
void update_nestness(node *sublist_branch)
{
    node *current = sublist_branch->next;

    // Iterate through sublist content.
    while (current != NULL)
    {
        // Check for nested content.
        if (current->type == NEST || current->type == LIST)
        {
>>>>>>> 7005796 (Implemented Testcases, Completed Documentation.)
            sublist_branch->type = NEST;
            return;
        }
        current = current->next;
    }
    // If no nested content found, set type to list.
    sublist_branch->type = LIST;
}

<<<<<<< HEAD
int store_data(node* mega_list, node* storage, char *data) {
    char *end = malloc(sizeof(char*));
>>>>>>> 0326015 (Testcases and error handling)

<<<<<<< HEAD
    // Remove newline character from input
    data[strcspn(data, "\n")] = '\0';

    int int_data = strtol(data, &end, 10);
    if (*end == '\0') {
        // Integer
=======
    // Strip trailing newline character
    data[strcspn(data, "\n")] = '\0';

    // Check if data is an integer
    int_data = strtol(data, &end, 10);
    if (*end == '\0') {
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> 49e025d (Implemented Error Handling and Resolved Memory Leaks)
=======
=======
// Stores data into a node based on its type and returns the type.
// Parameters: mega_list - pointer to the mega list, storage - pointer to the node to store data in,
//             data - string containing the data to be stored
// Returns: type of data stored in the node, or -1 if data could not be stored
// Store data into node based on type.
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
>>>>>>> 7005796 (Implemented Testcases, Completed Documentation.)
>>>>>>> b5e4d69 (Testcases, Documentation, Refactoring, and Finalizing)
        int *int_ptr = malloc(sizeof(int));
        if (int_ptr != NULL)
        {
            *int_ptr = int_data;
<<<<<<< HEAD
            storage->data = (void*)int_ptr;
            storage->type = INTEGER;
            return; // Return after storing integer
        }
    } 
    
<<<<<<< HEAD
    // Try parsing input as a float
=======
    // Check float
=======
            storage->data = (void *)int_ptr;
            return storage->type = INTEGER;
        }
        return -1; // Allocation failure
    }

    // Convert to float if possible.
>>>>>>> 7005796 (Implemented Testcases, Completed Documentation.)
>>>>>>> b5e4d69 (Testcases, Documentation, Refactoring, and Finalizing)
    float float_data = strtof(data, &end);
    if (*end == '\0')
    {
        // Allocate float.
        float *float_ptr = malloc(sizeof(float));
        if (float_ptr != NULL)
        {
            *float_ptr = float_data;
<<<<<<< HEAD
            storage->data = (void*)float_ptr;
<<<<<<< HEAD
            storage->type = FLOAT;
            return; // Return after storing float
=======
            return storage->type = FLOAT; 
=======
        int *int_ptr = (int*)malloc(sizeof(int));
        if (int_ptr == NULL) {
            printf("Memory allocation failed for integer data.\n");
            return ERROR;
>>>>>>> e7594d1 (Error handling and memory leaks)
>>>>>>> 49e025d (Implemented Error Handling and Resolved Memory Leaks)
        }
        *int_ptr = (int)int_data;
        storage->data = int_ptr;
        storage->type = INTEGER;
        return INTEGER;
    }
<<<<<<< HEAD
    
    // Check if input is a single character
    if (strlen(data) == 1) {
        // Character
=======

    // Check if data is a float
    float_data = strtof(data, &end);
    if (*end == '\0') {
        float *float_ptr = (float*)malloc(sizeof(float));
        if (float_ptr == NULL) {
            printf("Memory allocation failed for float data.\n");
            return ERROR;
        }
        *float_ptr = float_data;
        storage->data = float_ptr;
        storage->type = FLOAT;
        return FLOAT;
    }

    // Check if data is a single character
    if (strlen(data) == 1) {
<<<<<<< HEAD
>>>>>>> 49e025d (Implemented Error Handling and Resolved Memory Leaks)
        char *char_ptr = malloc(sizeof(char));
        if (char_ptr != NULL) {
            *char_ptr = *data;
            storage->data = (void*)char_ptr;
            storage->type = CHAR;
            return; // Return after storing character
        }
<<<<<<< HEAD
    } 
    
    // String
    char *str_ptr = malloc(strlen(data) + 1);
=======
    }//Check empty string
    else if (strlen(data) == 0){
        char *empty_ptr = malloc(1); 
        if (empty_ptr != NULL) {
            *empty_ptr = '\0';
            storage->data = (void*)empty_ptr;
            return storage->type = CHAR; 
=======
        char *char_ptr = (char*)malloc(sizeof(char));
        if (char_ptr == NULL) {
            printf("Memory allocation failed for char data.\n");
            return ERROR;
>>>>>>> e7594d1 (Error handling and memory leaks)
        }
        *char_ptr = data[0];
        storage->data = char_ptr;
        storage->type = CHAR;
        return CHAR;
    }

    // Check if data is an empty string
    if (strlen(data) == 0) {
        char *empty_ptr = (char*)malloc(1);
        if (empty_ptr == NULL) {
            printf("Memory allocation failed for empty string data.\n");
            return ERROR;
        }
        *empty_ptr = '\0';
        storage->data = empty_ptr;
        storage->type = STRING;
        return STRING;
    }

    // Otherwise, assume data is a string
    char *str_ptr = (char*)malloc(strlen(data) + 1);
    if (str_ptr == NULL) {
        printf("Memory allocation failed for string data.\n");
        return ERROR;
    }
<<<<<<< HEAD
=======
    
    // Check string or reference
    char *str_ptr = malloc(strlen(data) + 1);
    int list_id;
    node* reference;
>>>>>>> 0326015 (Testcases and error handling)
    strcpy(str_ptr, data);
<<<<<<< HEAD
>>>>>>> 49e025d (Implemented Error Handling and Resolved Memory Leaks)
    if (str_ptr != NULL) {
<<<<<<< HEAD
        strcpy(str_ptr, data);
        storage->data = (void*)str_ptr;
        storage->type = STRING;
=======
        if (str_ptr[0] == '{' && str_ptr[strlen(data) - 1] == '}' && sscanf(str_ptr, "{%d}", &list_id) == 1 && valid_id(mega_list, list_id)){
            //Reference
<<<<<<< HEAD
            storage->data = (void*)(find_sublist(mega_list, list_id));
            return storage->type = NEST;
=======
            reference = find_sublist(mega_list, list_id);
            if (reference->type == LIST){
                storage->data = (void*)reference;
                return storage->type = LIST;
            }else if(reference->type == NEST){
                return -1;
            }
            
>>>>>>> 0326015 (Testcases and error handling)
        }else{
            //String
            strcpy(str_ptr, data);
            storage->data = (void*)str_ptr;
            return storage->type = STRING;
        }
>>>>>>> 7560cf6 (Refined Input Handling, Bug Fixes, and Enhanced Error Handling)
    }
=======
    storage->data = str_ptr;
    storage->type = STRING;
=======
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
>>>>>>> 7005796 (Implemented Testcases, Completed Documentation.)
    return STRING;
>>>>>>> e7594d1 (Error handling and memory leaks)
}

<<<<<<< HEAD
void mtll_create(node **mega_list, int size, int new_list_id){

    // Create the head of the new list
=======
void mtll_create(node **mega_list, int size, int new_list_id) {
    // Create a new node for the head of the list
>>>>>>> 49e025d (Implemented Error Handling and Resolved Memory Leaks)
    node *head = (node*)malloc(sizeof(node));
    if (head == NULL) {
        printf("Memory allocation failed for head node.\n");
        return;
>>>>>>> f304311 (Part 1 Completed: NEW, VIEW, TYPE)
    }

<<<<<<< HEAD
    // Initialize the head of the new list
    char id[3];
    sprintf(id, "%d", new_list_id);
    store_data(head, id);
=======
    // Initialize the head of the new list with the list ID
    char id[12]; // Assuming list IDs can be represented in at most 11 characters
    snprintf(id, sizeof(id), "%d", new_list_id);
    store_data(*mega_list, head, id);
>>>>>>> 49e025d (Implemented Error Handling and Resolved Memory Leaks)
    head->next = NULL;
    head->type = INTEGER;

    // Populate the new list with nodes
    node *current = head;
    char input[MAX_INPUT_SIZE];

    for (int i = 0; i < size; i++) {
        fgets(input, sizeof(input), stdin);

<<<<<<< HEAD
        node* new_list_node = (node*)malloc(sizeof(node));
        if (new_list_node == NULL) {
            printf("Memory allocation failed for a new node in the list.\n");
            // Free allocated memory before returning
            while (head != NULL) {
                node *temp = head;
                head = head->next;
                free(temp);
            }
            return;
        }

        store_data(new_list_node, input);
        new_list_node->next = NULL;
=======
        node* new_node = (node*)malloc(sizeof(node));
        if (new_node == NULL) {
            printf("Memory allocation failed for a new node.\n");
            mtll_free(head);
            return;
        }

        if (store_data(*mega_list, new_node, input) < 0) {
            printf("Invalid data format.\n");
            free(new_node);
            continue;
        }
>>>>>>> 49e025d (Implemented Error Handling and Resolved Memory Leaks)

        new_node->next = NULL;

        current->next = new_node;
        current = new_node;
    }

<<<<<<< HEAD
    // Create a new node to hold the new list
    node *new_node = (node*)malloc(sizeof(node));
    if (new_node == NULL) {
        printf("Memory allocation failed for a new node.\n");
        // Free allocated memory before returning
        while (head != NULL) {
            node *temp = head;
            head = head->next;
            free(temp);
        }
        return;
    }

    // Initialize the new node
    new_node->data = head; // Set the data to point to the head of the new list
    new_node->type = LIST;
    new_node->next = NULL;

    // Link the new list node to the mega_list
    if (*mega_list == NULL) {
        *mega_list = new_node;
=======
    // Add the new list to the mega list
    if (*mega_list == NULL) {
        *mega_list = head;
>>>>>>> 49e025d (Implemented Error Handling and Resolved Memory Leaks)
    } else {
        node *last = *mega_list;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = head;
    }
}

<<<<<<< HEAD
<<<<<<< HEAD
void mtll_free(node *head){
=======
=======
>>>>>>> b5e4d69 (Testcases, Documentation, Refactoring, and Finalizing)

void free_node(node* node){//Free dynamically allocated memory of node and attributes.
    free(node->data);
    free(node);
=======
// Frees the memory allocated for a node.
// Parameters: Node - pointer to the node to be freed
void free_node(node *Node)
{ // Free dynamically allocated memory of node and attributes.
    if (Node->data != NULL && Node->type != LIST)
    {
        free(Node->data);
    }

    free(Node);
>>>>>>> 7005796 (Implemented Testcases, Completed Documentation.)
    return;
}
>>>>>>> 49e025d (Implemented Error Handling and Resolved Memory Leaks)

<<<<<<< HEAD
    // TODO
=======
// Frees the memory allocated for a list.
// Parameters: head - pointer to the node to be freed
// Free memory allocated for a list.
void mtll_free(node *head)
{
    node *current = head->next;

<<<<<<< HEAD
    if (head->next != NULL){
        mtll_free(head->next);
    }else{
        free_node(head);
=======
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

// Frees all dynamically allocated memory in the mega list.
//  Parameters: mega_list - pointer to the mega list
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
>>>>>>> 7005796 (Implemented Testcases, Completed Documentation.)
    }
    return;
>>>>>>> b5e4d69 (Testcases, Documentation, Refactoring, and Finalizing)
}

<<<<<<< HEAD
void print_node(node* element){
<<<<<<< HEAD
    if (element == NULL){
        printf("ERROR: NODE NOT FOUND");
    }
    switch (element->type){

=======
=======
// Prints the contents of a node.
// Parameters: element - pointer to the node
void print_node(node *element)
{
    node *sublist;
>>>>>>> 7005796 (Implemented Testcases, Completed Documentation.)

    switch (element->type)
    {

<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> b5e4d69 (Testcases, Documentation, Refactoring, and Finalizing)
        case LIST:
<<<<<<< HEAD
            printf("{List %d}", node->data);
            break;

        case INTEGER:
            printf("-> %d", node->data);
            break;

        case FLOAT:
            printf("%f", node->data);
            break;

        case CHAR:
            printf("%c", node->data);
            break;

        case STRING:
            printf("%s", node->data);
            break;

        default:
            printf('ERROR: TYPE UNKOWN');
=======
            node *sublist = element->data;
            printf("{List %d}", *(int*)sublist->data);
            break;
=======
    case LIST:
        sublist = (node *)element->data;
        printf("{List %d}", *(int *)(sublist->data));
        break;

    case NEST:
        sublist = (node *)element->data;
        printf("{List %d}", *(int *)(sublist->data));
        break;
>>>>>>> 7005796 (Implemented Testcases, Completed Documentation.)

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

<<<<<<< HEAD
        default:
            printf("ERROR: TYPE UNKOWN");
            break;
>>>>>>> f304311 (Part 1 Completed: NEW, VIEW, TYPE)

<<<<<<< HEAD
=======
=======
>>>>>>> f3491b1 (Semi-final iteration)
=======
    default:
        printf("ERROR: TYPE UNKOWN");
        break;
>>>>>>> 7005796 (Implemented Testcases, Completed Documentation.)
>>>>>>> b5e4d69 (Testcases, Documentation, Refactoring, and Finalizing)
    }
}

// Prints the type of a node.
// Parameters: node - pointer to the node
void print_node_type(node *node)
{
    if (node == NULL){
<<<<<<< HEAD
        prtinf('ERROR: NODE NOT FOUND');
=======
        printf("ERROR: NODE NOT FOUND");
>>>>>>> f304311 (Part 1 Completed: NEW, VIEW, TYPE)
    }

    switch (node->type)
    {

<<<<<<< HEAD
        case LIST:
=======
<<<<<<< HEAD
        case NEST:
>>>>>>> b5e4d69 (Testcases, Documentation, Refactoring, and Finalizing)
            printf("reference");
            break;
=======
    case NEST:
        printf("reference");
        break;
>>>>>>> 7005796 (Implemented Testcases, Completed Documentation.)

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

<<<<<<< HEAD
        default:
<<<<<<< HEAD
            printf('ERROR: TYPE UNKOWN');
=======
            printf("ERROR: TYPE UNKOWN");
            break;
>>>>>>> f304311 (Part 1 Completed: NEW, VIEW, TYPE)
=======
    case STRING:
        printf("string");
        break;
>>>>>>> 7005796 (Implemented Testcases, Completed Documentation.)

    default:
        printf("ERROR: TYPE UNKOWN");
        break;
    }
    return;
}

<<<<<<< HEAD
void mtll_print_list(node* head, printMode mode){
    node* current = head;

    // Print the data of the current node and move to the next node
    while (current != NULL){
        if(mode == DATA){print_node(current);}
        else if (mode == TYPE) {print_node_type(current);}
        if (current->next != NULL) {
            printf(" -> ");
=======
// Prints the contents or types of nodes in a list based on the specified mode.
// Parameters: head - pointer to the head of the list, mode - mode indicating whether to print data or types
// Print contents or types of nodes in a list.
void mtll_print_list(node *head, printMode mode)
{
    node *current = head;

    // Iterate through nodes in the list and print their contents or types based on the mode.
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
            {
                printf("{");
                mtll_print_list((node *)(((node *)current->data)->next), DATA); // Print contents of nested node
                printf("}");
            }
        }
        if (current->next != NULL)
        {
            printf(" -> "); // Print separator if there are more nodes
>>>>>>> b5e4d69 (Testcases, Documentation, Refactoring, and Finalizing)
        }
        current = current->next;
    }
    printf("\n"); // Print a newline character at the end
}

<<<<<<< HEAD
void mtll_view(node *mega_list, int list_id, printMode mode, int mega_size) {
    node* sublist_head = element_from_index(mega_list, list_id, mega_size)->next;

<<<<<<< HEAD
    // If index is out of bounds, or current is NULL
    if (current != NULL) {
        mtll_print_list(current);
    }else{
        invalid_command("VIEW");
    }
    
    return;
}

element_from_index(node *head, int index, char* command){
    node *current = head;

    int i = 0;
    for (int i = 0; i < index; i++){

        if (current != NULL){
            current = current->next;

        }else{
            printf("INVALID COMMAND: %s", command);

        }
=======
    // If the list with the given index is found
<<<<<<< HEAD
    if (current != NULL && current->data != NULL) {
        node* sublist = current->data;
        mtll_print_list(sublist->next, mode); // Access the sublist to print its contents
>>>>>>> f304311 (Part 1 Completed: NEW, VIEW, TYPE)
=======
    if (sublist_head != NULL) {
=======
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
>>>>>>> 7005796 (Implemented Testcases, Completed Documentation.)
        mtll_print_list(sublist_head, mode); // Access the sublist to print its contents
>>>>>>> 1505f78 (Added: mtll_insert Fixed: mtll_view, delete)
<<<<<<< HEAD
    }
}

=======
=======
        printf("\n");
<<<<<<< HEAD
>>>>>>> f3491b1 (Semi-final iteration)
    }
}

void recap(node* sublist_branch){
    //Recap of list contents after manipulations.
    node* sublist_head = sublist_branch->next;
    if (sublist_branch->type == LIST){
        printf("List %d: ", *(int*)(sublist_branch->data));
    }else{
        printf("Nested %d: ", *(int*)(sublist_branch->data));
=======
    }
}

// Prints the list number and contents.
// Parameters: sublist_branmch - pointer to the sublist to print
void recap(node *sublist_branch)
{
    node *sublist_head = sublist_branch->next;
    if (sublist_branch->type == NEST)
    {
        printf("Nested %d: ", *(int *)(sublist_branch->data));
    }
    else
    {
        printf("List %d: ", *(int *)(sublist_branch->data));
>>>>>>> 7005796 (Implemented Testcases, Completed Documentation.)
    }
    mtll_print_list(sublist_head, DATA);
    printf("\n");
    return;
}

<<<<<<< HEAD
>>>>>>> b5e4d69 (Testcases, Documentation, Refactoring, and Finalizing)
void mtll_view_all(node **mega_list, int mega_size){
    if (*mega_list == NULL) {
        printf("Mega list is empty.\n");
=======
// Prints a summary of all existing lists in the mega list.
// Parameters: mega_list - pointer to the pointer to the mega list, mega_size - size of the mega list
void mtll_view_all(node **mega_list, int mega_size)
{
    if (*mega_list == NULL)
    {
        printf("Number of lists: 0\n");
>>>>>>> 7005796 (Implemented Testcases, Completed Documentation.)
        return;
    }

    printf("Number of lists: %d\n", mega_size);

<<<<<<< HEAD
=======
<<<<<<< HEAD
    //If the mega_list is empty
>>>>>>> b5e4d69 (Testcases, Documentation, Refactoring, and Finalizing)
    if (*mega_list == NULL) {
        invalid_command("VIEW ALL");
        return;
    }

    node *current = *mega_list;
    while (current != NULL){
        printf("List %d\n", get_list_id(current));
=======
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
>>>>>>> 7005796 (Implemented Testcases, Completed Documentation.)
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

<<<<<<< HEAD
int mtll_remove(node **mega_list, int list_id, int mega_size){
    node* current = *mega_list;
    node* target;

    // Check if the first node matches the target ID
    if(get_list_id(current) == list_id){
<<<<<<< HEAD
        *mega_list = (*mega_list)->next; // Update mega_list to skip the first node
        free(current); // Free the memory of the removed node
        return;
    }

    // Traverse the list to find the node with the target ID
    while (current != NULL) {
        if (get_list_id(current->next) == list_id){
            target = current->next; // Found the target node
            break;
        }
        current = current->next; // Move to the next node
    }
    
    if(target != NULL){ //Free memory
        current->next = target->next; //Remove linkage
        free(target); //Free memory
    }
    mtll_view_all(mega_list, mega_size);
    return;
=======
        if (has_reference(*mega_list, list_id) == 0){
            *mega_list = (*mega_list)->next; //Remove linkage to first sublist
            mtll_free(current->data);
            free(current);
        }else{
=======
    // Remove sublist by ID
    if (get_list_id(current) == list_id)
    {
        if (has_reference(*mega_list, list_id) == 0)
            *mega_list = (*mega_list)->next; // Remove linkage to first sublist
        else
        {
>>>>>>> 7005796 (Implemented Testcases, Completed Documentation.)
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
<<<<<<< HEAD
        }if(target != NULL && has_reference(*mega_list, list_id) == 0){ //If the sublist exists
            current->next = target->next; //Remove linkage to deleted sublist from megalist
            mtll_free(target->data); 
            free(target);
        }else{
=======
        }
        if (target != NULL && has_reference(*mega_list, list_id) == 0)
            current->next = target->next; // Remove linkage to deleted sublist from megalist
        else
        {
>>>>>>> 7005796 (Implemented Testcases, Completed Documentation.)
            invalid_command("REMOVE");
            return 0;
        }
    }
    else
    {
        invalid_command("REMOVE");
        return 0;
    }
<<<<<<< HEAD
=======

    // Free memory allocated for the sublist
    mtll_free(target->data);
    free(target);
>>>>>>> 7005796 (Implemented Testcases, Completed Documentation.)
    printf("List %d has been removed.\n\n", list_id);
    mtll_view_all(mega_list, mega_size - 1);
    return 1;
<<<<<<< HEAD
    
    
    
>>>>>>> 7560cf6 (Refined Input Handling, Bug Fixes, and Enhanced Error Handling)
=======
>>>>>>> b5e4d69 (Testcases, Documentation, Refactoring, and Finalizing)
}
<<<<<<< HEAD
<<<<<<< HEAD
=======
int mtll_create(node **mega_list, int size, int new_list_id){
=======
>>>>>>> 7005796 (Implemented Testcases, Completed Documentation.)

// Creates a new sublist and adds it to the mega list.
// Parameters: mega_list - pointer to the pointer to the mega list, size - size of the new sublist,
//             new_list_id - ID of the new sublist
// Returns: 1 if the new sublist is successfully created and added, 0 otherwise
int mtll_create(node **mega_list, int size, int new_list_id)
{
    // Create head of new list
    node *head = (node *)malloc(sizeof(node));
    if (head == NULL)
    {
        printf("Memory allocation failed for the head of the new list.\n");
        return 0;
    }

<<<<<<< HEAD
    // Initialize the head of the new list
    char id[3];
=======
    // Initialize head of the new list
    char *id = malloc(3);
>>>>>>> 7005796 (Implemented Testcases, Completed Documentation.)
    sprintf(id, "%d", new_list_id);
    store_data(*mega_list, head, id);
    head->type = LIST;
    head->next = NULL;

    // Populate the new list
    node *current = head;
    char input[MAX_INPUT_SIZE + 1];
    dataType type;

<<<<<<< HEAD
    node *new_node = (node*)malloc(sizeof(node));
    if (new_node == NULL) {
        free(new_node);
        mtll_free(head);
    }

    for (int i = 0; i < size; i++) {
        fgets(input, sizeof(input), stdin);

        node* new_list_node = (node*)malloc(sizeof(node));
        if (new_list_node == NULL) {
            while (head != NULL) {
                node *temp = head;
                head = head->next;
                free(temp);
            }
            return 0;
        }
=======
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
>>>>>>> 7005796 (Implemented Testcases, Completed Documentation.)

        // Store data into new_list_node
        type = store_data(*mega_list, new_list_node, input);

<<<<<<< HEAD
        if (type == LIST || type == NEST){
            head->type = NEST;
        }else if(type == -1){
            free(new_node);
=======
        // Update type of head if nested list
        if (type == LIST)
        {
            head->type = NEST;
        }
        else if (type == -1)
        {
>>>>>>> 7005796 (Implemented Testcases, Completed Documentation.)
            free(new_list_node);
            mtll_free(head);
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
    else
    {
        node *last = *mega_list;
        while (last->next != NULL)
        {
            last = last->next;
        }
        last->next = new_node;
    }
    recap(new_node->data);
    return 1;
}
>>>>>>> 0326015 (Testcases and error handling)

<<<<<<< HEAD
void mtll_delete(node *mega_list, int list_id, int index, int mega_size) {
    // Find the sublist corresponding to the given list_id
    node *sublist_head = NULL;
    node *current = mega_list;
    while (current != NULL) {
        if (get_list_id(current) == list_id) {
            sublist_head = current->data;
            break;
        }
        current = current->next;
    }

    int size;
    if(index < 0 || index > size){
        if (index > size){
            invalid_command("DELETE(out of bounds)");
            return;
        }
        index = size + index;
        if(index < 0){
            invalid_command("DELETE(out of bounds)");
=======
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
>>>>>>> b5e4d69 (Testcases, Documentation, Refactoring, and Finalizing)
            return;
        }
    }

    // Traverse the list to find the node to delete
    node *prev = NULL;
<<<<<<< HEAD
    current = sublist_head;
=======
    node *current = sublist_head;
>>>>>>> b5e4d69 (Testcases, Documentation, Refactoring, and Finalizing)
    int i = 0;
    while (current != NULL && i < index)
    {
        prev = current;
        current = current->next;
        i++;
    }

<<<<<<< HEAD
    // If node to delete is found
    if (current != NULL) {
        // Update pointers to skip the node to be deleted
        if (prev != NULL) {
            prev->next = current->next;
        } else {
            // If deleting the head node
=======
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
>>>>>>> b5e4d69 (Testcases, Documentation, Refactoring, and Finalizing)
            sublist_head = current->next;
        }
        // Free memory for the node
<<<<<<< HEAD
        free(current);
    } else {
<<<<<<< HEAD
        invalid_command("DELETE(missing index)");
=======
=======
    }
    else
    {
>>>>>>> 7005796 (Implemented Testcases, Completed Documentation.)
        invalid_command("DELETE");
        return;
>>>>>>> b5e4d69 (Testcases, Documentation, Refactoring, and Finalizing)
    }
<<<<<<< HEAD
=======
    update_nestness(sublist_branch);
    recap(sublist_branch);
>>>>>>> 7560cf6 (Refined Input Handling, Bug Fixes, and Enhanced Error Handling)
}

<<<<<<< HEAD
<<<<<<< HEAD
void mtll_insert(node *mega_list, int list_id, int index, int mega_size){
    
}
=======
void mtll_insert(node **mega_list, int list_id, int index, int mega_size, char* data) {
=======
// Inserts a node into a sublist in a mega list.
// Parameters: mega_list - pointer to the pointer to the mega list, list_id - ID of the sublist to insert into,
//             index - index at which to insert the node, mega_size - size of the mega list, data - data to insert
void mtll_insert(node **mega_list, int list_id, int index, int mega_size, char *data)
{
>>>>>>> b5e4d69 (Testcases, Documentation, Refactoring, and Finalizing)
    // Find the sublist corresponding to the given list_id
    node *sublist_branch = find_sublist(*mega_list, list_id);
    node *sublist_head = sublist_branch->next;

    int size = get_list_size(sublist_head);

<<<<<<< HEAD
=======
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

>>>>>>> 7005796 (Implemented Testcases, Completed Documentation.)
    // Create a new node
    node *new_node = (node *)malloc(sizeof(node));
    if (new_node == NULL)
    {
        return;
    }
    int type = store_data(*mega_list, new_node, data); // Store data into new_node
<<<<<<< HEAD
    if (type == -1){
=======
    if (type == -1 || (type == LIST && has_reference(*mega_list, list_id)))
    {
>>>>>>> 7005796 (Implemented Testcases, Completed Documentation.)
        invalid_command("INSERT");
        return;
    }

<<<<<<< HEAD
    if (index < 0 || index > size) {
        // If the index is out of bounds, insert at the end of the sublist
        if (index > size) {
            invalid_command("INSERT(out of bounds)");
            return;
        }
        index = size; // Adjust the index to the end of the sublist
    }

    if (size == 0 || index == 0) {
=======
    if (size == 0 || index == 0)
    {
>>>>>>> 7005796 (Implemented Testcases, Completed Documentation.)
        // If the sublist is empty or inserting at index 0, set the new_node as the sublist head
        new_node->next = sublist_head;
        sublist_branch->next = new_node;
<<<<<<< HEAD
        sublist_head = sublist_branch->next;
    } else {
=======
    }
    else
    {
>>>>>>> 7005796 (Implemented Testcases, Completed Documentation.)
        // If the sublist is not empty or inserting at an index greater than 0
        node *prev = NULL;
        node *current = sublist_head;
        int i = 0;
<<<<<<< HEAD
        while (current != NULL && i != index) {
=======
        while (current != NULL && i < index)
        {
>>>>>>> 7005796 (Implemented Testcases, Completed Documentation.)
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

<<<<<<< HEAD
    //If we are inserting a list reference, update head to indicate that is contains a nested list.
    if(new_node->type == LIST){
            sublist_head->type = NEST;
=======
    // If we are inserting a list reference, update head to indicate that is contains a nested list.
    if (new_node->type == LIST)
    {
        find_sublist(*mega_list, list_id)->type = NEST;
>>>>>>> 7005796 (Implemented Testcases, Completed Documentation.)
    }
    update_nestness(sublist_branch);
    recap(sublist_branch);
}


>>>>>>> 49e025d (Implemented Error Handling and Resolved Memory Leaks)
