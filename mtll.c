#include "mtll.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_INPUT_SIZE (128)

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
    if (sublist != NULL) {
        return *((int*)(sublist->data));
    }else {
        // Handle error: sublist or sublist->data is NULL
        return -1; // Return a default value to indicate failure
    }
}


int valid_id(node* mega_list, int list_id){
    

    if(list_id < 1){
        return 0;
    }
    
    node *current = mega_list;
    while(current != NULL){
        if (get_list_id(current->data) == list_id){
            return 1;
        }
        current = current->next;
    }
    return 0;
}



void invalid_command(char* command)
{
    printf("INVALID COMMAND: %s\n", command);
    return;
}



node* element_from_index(node *head, int index, char* command){
    node *current = head;

    while (current != NULL){
        if ((*(int*)current->data == index)){
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void store_data(node* storage, char *data) {
    char *end;

    // Remove newline character from input
    data[strcspn(data, "\n")] = '\0';

    int int_data = strtol(data, &end, 10);
    if (*end == '\0') {
        // Integer
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
            storage->type = FLOAT;
            return; // Return after storing float
        }
    }
    
    // Check if input is a single character
    if (strlen(data) == 1) {
        // Character
        char *char_ptr = malloc(sizeof(char));
        if (char_ptr != NULL) {
            *char_ptr = *data;
            storage->data = (void*)char_ptr;
            storage->type = CHAR;
            return; // Return after storing character
        }
    } 
    
    // String
    char *str_ptr = malloc(strlen(data) + 1);
    if (str_ptr != NULL) {
        strcpy(str_ptr, data);
        storage->data = (void*)str_ptr;
        storage->type = STRING;
    }
}

void mtll_create(node **mega_list, int size, int new_list_id){

    // Create the head of the new list
    node *head = (node*)malloc(sizeof(node));
    if (head == NULL) {
        printf("Memory allocation failed for the head of the new list.\n");
        return;
>>>>>>> f304311 (Part 1 Completed: NEW, VIEW, TYPE)
    }

    // Initialize the head of the new list
    char id[3];
    sprintf(id, "%d", new_list_id);
    store_data(head, id);
    head->next = NULL;
    head->type = INTEGER;

    // Populate the new list
    node *current = head;
    char input[MAX_INPUT_SIZE];

    for (int i = 0; i < size; i++) {
        fgets(input, sizeof(input), stdin);

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

        current->next = new_list_node;
        current = new_list_node;
    }

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
    } else {
        node *last = *mega_list;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = new_node;
    }
}

void mtll_free(node *head){

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



void mtll_view(node *mega_list, int index, printMode mode) {
    // Check if mega_list is empty

    node *current = mega_list;

    // Traverse linked list searching for node with ID==index.
    while (current != NULL) {
        if (get_list_id(current->data) == index) {
            break;
        }
        current = current->next;
    }

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
    if (current != NULL && current->data != NULL) {
        node* sublist = current->data;
        mtll_print_list(sublist->next, mode); // Access the sublist to print its contents
>>>>>>> f304311 (Part 1 Completed: NEW, VIEW, TYPE)
    }
}



void mtll_view_all(node **mega_list, int mega_size){
    
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

void mtll_remove(node *mega_list, int list_id){
    node* current = mega_list;

    while (current != NULL) {
        if (*(int*)current->data == list_id){
            free(current);
            break;
        }
        current = current->next;
    }

    if (current == NULL) {
        invalid_command("REMOVE");
    }
}

void mtll_delete_element(node *mega_list, int list_id, int index){
    return;
}

void mtll_print_types(node* head){
    print_node_type(head);
    node* current = head->next;

    while (current!=NULL){
        if(current->type == LIST)
        print_node(current);
        current = current->next;
    }
    return;
}

void mtll_view_types(node *mega_list, int list_id){
    int count = 0;
    node *current = mega_list;
    
    // Traverse linked list searching for node with ID==index.
    while (current != NULL) {
        if (*(int*)current->data == list_id){
            break;
        }
        current = current->next;
        count++;
    }

    // If index is out of bounds, or current is NULL
    if (current != NULL) {
        mtll_print_types(current);
    }else{
        invalid_command("TYPE");
    }
    
    return;
}