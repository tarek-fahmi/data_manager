#ifndef MTLL_H

#define MTLL_H

#include <stdlib.h>

typedef struct node
{
    void *data;
    dataType type;
    node *next;

} node;

typedef enum
{

    INTEGER,

    FLOAT,

    CHAR,

    STRING,

    LIST

} dataType;

// A few suggested function prototypes:

// Feel free to change or improve these as you need.
extern void invalid_command(char* command);

extern void mtll_create(node** mega_list, int size, int new_list_id);

extern void mtll_free(node *head);

extern void mtll_view(node* head, int index);

extern void mtll_view_all(node **mega_list, int mega_size);

extern void mtll_view_types(node *head); //Complete testing

extern void mtll_remove(node **head, node *node); //Finish this

extern void mtll_insert_element(node **mega_list, int list_id, int index); //TODO

extern void mtll_delete_element(node **mega_list, int list_id, int index); //TODO

extern node* mtll_list_reference(node ** mega_list, int list_id); //TODO


<<<<<<< HEAD
extern void mtll_remove(struct mtll **, , size_t, struct mtll *);
=======
>>>>>>> c4bc6d5 (First implentation: Implemented basic features.)

// You will likely need other functions for Parts 2 and 3,

// And for general input / output management

#endif