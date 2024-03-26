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

<<<<<<< HEAD
=======
typedef enum{

    DATA,

    TYPE

} printMode;

typedef struct node
{
    void *data;
    dataType type;
    struct node *next;

} node;



>>>>>>> f304311 (Part 1 Completed: NEW, VIEW, TYPE)
// A few suggested function prototypes:

// Feel free to change or improve these as you need.
extern void invalid_command(char* command);

extern int valid_id(node* mega_list, int list_id);

extern void print_node(node* node);

extern void mtll_create(node** mega_list, int size, int new_list_id);

extern void mtll_free(node *head); //TODO

<<<<<<< HEAD
<<<<<<< HEAD
extern void mtll_view(node* head, int index);
=======
extern void mtll_view(node* mega_list, int index, printMode mode);
>>>>>>> f304311 (Part 1 Completed: NEW, VIEW, TYPE)
=======
extern void mtll_view(node* mega_list, int index, printMode mode, int mega_size);
>>>>>>> 1505f78 (Added: mtll_insert Fixed: mtll_view, delete)

extern void mtll_view_all(node **mega_list, int mega_size);

extern void mtll_remove(node **mega_list, int list_id, int mega_size); //MAKE THIS FREE THE LIST RATHER THAN ONLY THE REFERENCE

extern void mtll_insert(node *mega_list, int list_id, int index, int mega_size); //TODO

extern void mtll_delete(node *mega_list, int list_id, int index, int mega_size); //TODO

extern node* mtll_list_reference(node * mega_list, int list_id); //TODO


<<<<<<< HEAD
extern void mtll_remove(struct mtll **, , size_t, struct mtll *);
=======
>>>>>>> c4bc6d5 (First implentation: Implemented basic features.)

// You will likely need other functions for Parts 2 and 3,

// And for general input / output management

#endif