#include "mtll.h"

#include <stdlib.h>

#include <stdio.h>

#define MAX_INPUT_SIZE (128)

invalid_command(char* command)
{
    printf("INVALID COMMAND: %s", command);
}

void print_node(node* node){
    if (node == NULL){
        prtinf('ERROR: NODE NOT FOUND');
    }

    switch (node->type){

        case LIST:
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

    }
}

void print_node_type(node* node){
    if (node == NULL){
        prtinf('ERROR: NODE NOT FOUND');
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
            printf('ERROR: TYPE UNKOWN');

    }
}

void mtll_print_list(node* head){
    print_node(head);
    node* current = head->next;

    while (current!=NULL){
        if(current->type == LIST)
        print_node(current);
        current = current->next;
    }
    return;
}

void mtll_view(node **mega_list, int index){
    int count = 0;
    node *current = *mega_list;
    
    // Traverse linked list searching for node with ID==index.
    while (current != NULL) {
        if (current->data == index){
            break;
        }
        current = current->next;
        count++;
    }

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
    }
}

void* store_data(char *data) {
    char *end;
    void *new_data = NULL;

    int int_data = strtol(data, &end, 10);
    if (*end == '\0') {
        // Integer
        int *int_ptr = malloc(sizeof(int));
        if (int_ptr != NULL) {
            *int_ptr = int_data;
            new_data = int_ptr;
        }
    } else {
        // Float
        float float_data = strtof(data, &end);
        if (*end == '\0') {
            float *float_ptr = malloc(sizeof(float));
            if (float_ptr != NULL) {
                *float_ptr = float_data;
                new_data = float_ptr;
            }
        } else{
            // Character or string
            if (strlen(data) == 1) {
                // Character
                char *char_ptr = malloc(sizeof(char));
                if (char_ptr != NULL) {
                    *char_ptr = *data;
                    new_data = char_ptr;
                }
            } else {
                // String
                char *str_ptr = malloc(strlen(data) + 1);
                if (str_ptr != NULL) {
                    strcpy(str_ptr, data);
                    new_data = str_ptr;
                }
            }
        }
    }
    return new_data;
}


void mtll_create(node** mega_list, int size, int new_list_id){

    node *head = (node*)malloc(sizeof(node));
    node *current = head;

    char id[3];
    sprintf(id, "%d", new_list_id);
    head->data = store_data(id);
    head->next = NULL;

    char input[MAX_INPUT_SIZE];

    for (int i = 0; i < size; i++) {
        //Prompt user to enter element i of list.
        fgets(input, sizeof(input), stdin);

        //Allocate memory for the new node.
        node* new_node = (node*)malloc(sizeof(node));

        //Check if new node successfully allocated.
        if (new_node == NULL) {
            printf("Memory allocation failed for a new node.\n");
            // Cleanup already allocated nodes before returning
            return;
        }aa

        //Store new node data.
        new_node->data = store_data(input);
        new_node->next = NULL;

        //Link previous node to new node and move to next.
        current->next = new_node;
        current = current->next;
    }

    if(*mega_list == NULL){
        //If the mega list is currently empty, store this in the first index.
        *mega_list = head;
        (*mega_list)->data = new_list_id;
        (*mega_list)->next = NULL;
    }else{
        current = *mega_list;
        while (current->next != NULL){
            current = current->next;
        }
        current->next = head;
        //Add new list to mega_list and record id.
    }
}

void mtll_free(node *head){

    // TODO
}


void mtll_view_all(node **all_lists, int mega_size){
    
    printf("Number of lists: %d\n", mega_size);

    node *current = *all_lists;
    while (current != NULL){

        printf("List %d\n", current->data);
        current = current->next;
    }
}

void mtll_remove(node **mega_list, int list_id){
    node* head = *mega_list;
    struct node* current = head;

    while (current != NULL) {
        if (current->data == list_id){
            free(current);
            break;
        }
        current = current->next;
    }

    if (current == NULL) {
        invalid_command("REMOVE");
    }
}

void mtll_delete_element(node **head, int index){

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

void mtll_view_types(node **mega_list, int index){
    int count = 0;
    node *current = *mega_list;
    
    // Traverse linked list searching for node with ID==index.
    while (current != NULL) {
        if (current->data == index){
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