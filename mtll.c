#include "mtll.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_INPUT_SIZE (128)
#define ERROR (0)

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
        // Handle error: sublist or sublist->data is NULL
        return -1; // Return a default value to indicate failure
    }
}

int has_reference(node* mega_list, int list_id){
    node* i = mega_list;
    node* reference_head;

    while (i != NULL){
        node* j = (node*)((node*)i->data)->next;
        while(j != NULL){
            if (j->type == LIST || j->type == NEST){
                reference_head = j->data;
                if (*((int*)(reference_head->data)) == list_id){
                    return 1;
                }
            }
            j = j->next;
        }
        i = i->next;
    }
    return 0;  // No reference found
}


int get_list_size(node* head){
    node* current = head;
    int size = 0;
    while (current != NULL){
        size++;
        current = current->next;
    }
    return size;
}

int valid_id(node* mega_list, int list_id){
    if(list_id < 1){
        return 0;
    }
    
    node *current = mega_list;
    while(current != NULL){
        if (get_list_id(current) == list_id){
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void invalid_command(char* command){
    printf("INVALID COMMAND: %s\n", command);
    return;
}

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
            sublist_branch->type = NEST;
            return;
        }
        current = current->next;
    }
    sublist_branch->type = LIST;
}

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
>>>>>>> 49e025d (Implemented Error Handling and Resolved Memory Leaks)
        int *int_ptr = malloc(sizeof(int));
        if (int_ptr != NULL) {
            *int_ptr = int_data;
            storage->data = (void*)int_ptr;
            storage->type = INTEGER;
            return; // Return after storing integer
        }
    } 
    
    // Try parsing input as a float
    float float_data = strtof(data, &end);
    if (*end == '\0') {
        float *float_ptr = malloc(sizeof(float));
        if (float_ptr != NULL) {
            *float_ptr = float_data;
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
void mtll_free(node *head){
=======

void free_node(node* node){//Free dynamically allocated memory of node and attributes.
    free(node->data);
    free(node);
    return;
}
>>>>>>> 49e025d (Implemented Error Handling and Resolved Memory Leaks)

    // TODO
}

void print_node(node* element){
    if (element == NULL){
        printf("ERROR: NODE NOT FOUND");
    }
    switch (element->type){

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

        case INTEGER:
            printf("%d", *(int*)element->data);
            break;

        case FLOAT:
            printf("%.2f", *(float*)element->data);
            break;

        case CHAR:
            printf("%c", *(char*)element->data);
            break;

        case STRING:
            printf("%s", (char*)element->data);
            break;

        default:
            printf("ERROR: TYPE UNKOWN");
            break;
>>>>>>> f304311 (Part 1 Completed: NEW, VIEW, TYPE)

    }
}

void print_node_type(node* node)
{
    if (node == NULL){
<<<<<<< HEAD
        prtinf('ERROR: NODE NOT FOUND');
=======
        printf("ERROR: NODE NOT FOUND");
>>>>>>> f304311 (Part 1 Completed: NEW, VIEW, TYPE)
    }

    switch (node->type){

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
<<<<<<< HEAD
            printf('ERROR: TYPE UNKOWN');
=======
            printf("ERROR: TYPE UNKOWN");
            break;
>>>>>>> f304311 (Part 1 Completed: NEW, VIEW, TYPE)

    }
    return;
}

void mtll_print_list(node* head, printMode mode){
    node* current = head;

    // Print the data of the current node and move to the next node
    while (current != NULL){
        if(mode == DATA){print_node(current);}
        else if (mode == TYPE) {print_node_type(current);}
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n"); // Print a newline character at the end
}

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
        mtll_print_list(sublist_head, mode); // Access the sublist to print its contents
>>>>>>> 1505f78 (Added: mtll_insert Fixed: mtll_view, delete)
    }
}

void mtll_view_all(node **mega_list, int mega_size){
    if (*mega_list == NULL) {
        printf("Mega list is empty.\n");
        return;
    }

    printf("Number of lists: %d\n", mega_size);

    if (*mega_list == NULL) {
        invalid_command("VIEW ALL");
        return;
    }

    node *current = *mega_list;
    while (current != NULL){
        printf("List %d\n", get_list_id(current));
        current = current->next;
    }
}


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
            invalid_command("REMOVE");
            return 0;
        }
    }
    else if (mega_size > 0){
            //Search for requested id
        while (current != NULL) {
            if (get_list_id(current->next) == list_id){
                target = current->next; //Found the sublist with requested id
                break;
            }
            current = current->next;
        }if(target != NULL && has_reference(*mega_list, list_id) == 0){ //If the sublist exists
            current->next = target->next; //Remove linkage to deleted sublist from megalist
            mtll_free(target->data); 
            free(target);
        }else{
            invalid_command("REMOVE");
            return 0;
        }
        
    }else{
        invalid_command("REMOVE");
        return 0;
    }
    printf("List %d has been removed.\n\n", list_id);
    mtll_view_all(mega_list, mega_size - 1);
    return 1;
    
    
    
>>>>>>> 7560cf6 (Refined Input Handling, Bug Fixes, and Enhanced Error Handling)
}
<<<<<<< HEAD
=======
int mtll_create(node **mega_list, int size, int new_list_id){

    // Head of new list
    node *head = (node*)malloc(sizeof(node));
    if (head == NULL) {
        printf("Memory allocation failed for the head of the new list.\n");
        return 0;
    }

    // Initialize the head of the new list
    char id[3];
    sprintf(id, "%d", new_list_id);
    store_data(*mega_list, head, id);
    head->type = LIST;
    head->next = NULL;

    // Populate the new list
    node *current = head;
    char input[MAX_INPUT_SIZE];
    dataType type;

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

        type = store_data(*mega_list, new_list_node, input);

        if (type == LIST || type == NEST){
            head->type = NEST;
        }else if(type == -1){
            free(new_node);
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
    new_node->data = head; //New megalist node points to head of new list
    new_node->next = NULL;

    
    if (*mega_list == NULL) { //If megalist is empty, initialize first element
        *mega_list = new_node;
    } else {
        node *last = *mega_list; //If megalist is not empty, find the last index and add a new node
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = new_node;
    }
    recap(new_node->data);
    return 1;
}
>>>>>>> 0326015 (Testcases and error handling)

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
            return;
        }
    }

    // Traverse the list to find the node to delete
    node *prev = NULL;
    current = sublist_head;
    int i = 0;
    while (current != NULL && i < index) {
        prev = current;
        current = current->next;
        i++;
    }

    // If node to delete is found
    if (current != NULL) {
        // Update pointers to skip the node to be deleted
        if (prev != NULL) {
            prev->next = current->next;
        } else {
            // If deleting the head node
            sublist_head = current->next;
        }
        // Free memory for the node
        free(current);
    } else {
        invalid_command("DELETE(missing index)");
    }
<<<<<<< HEAD
=======
    update_nestness(sublist_branch);
    recap(sublist_branch);
>>>>>>> 7560cf6 (Refined Input Handling, Bug Fixes, and Enhanced Error Handling)
}

<<<<<<< HEAD
void mtll_insert(node *mega_list, int list_id, int index, int mega_size){
    
}
=======
void mtll_insert(node **mega_list, int list_id, int index, int mega_size, char* data) {
    // Find the sublist corresponding to the given list_id
    node* sublist_branch = find_sublist(*mega_list, list_id);
    node* sublist_head = sublist_branch->next;

    int size = get_list_size(sublist_head);

    // Create a new node
    node* new_node = (node*)malloc(sizeof(node));
    if (new_node == NULL) {
        return;
    }
    int type = store_data(*mega_list, new_node, data); // Store data into new_node
    if (type == -1){
        invalid_command("INSERT");
        return;
    }

    if (index < 0 || index > size) {
        // If the index is out of bounds, insert at the end of the sublist
        if (index > size) {
            invalid_command("INSERT(out of bounds)");
            return;
        }
        index = size; // Adjust the index to the end of the sublist
    }

    if (size == 0 || index == 0) {
        // If the sublist is empty or inserting at index 0, set the new_node as the sublist head
        new_node->next = sublist_head;
        sublist_branch->next = new_node;
        sublist_head = sublist_branch->next;
    } else {
        // If the sublist is not empty or inserting at an index greater than 0
        node *prev = NULL;
        node *current = sublist_head;
        int i = 0;
        while (current != NULL && i != index) {
            prev = current;
            current = current->next;
            i++;
        }

        // Update pointers to insert the new node
        if (prev != NULL) { //Not inserting at head
            prev->next = new_node;
        } else { //Inserting at head
            *mega_list = new_node;
        }
        
        new_node->next = current;
    }

    //If we are inserting a list reference, update head to indicate that is contains a nested list.
    if(new_node->type == LIST){
            sublist_head->type = NEST;
    }
    update_nestness(sublist_branch);
    recap(sublist_branch);
}


>>>>>>> 49e025d (Implemented Error Handling and Resolved Memory Leaks)
