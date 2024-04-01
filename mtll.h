#ifndef MTLL_H
#define MTLL_H

#include <stdlib.h>

typedef enum
{

    INTEGER,

    FLOAT,

    CHAR,

    STRING,

    LIST,

    NEST

} dataType;

typedef enum{

    DATA,

    TYPE,

    NESTED

} printMode;

typedef struct node
{
    void *data;
    dataType type;
    struct node *next;
    int protected;

} node;



// Function prototypes:
extern void invalid_command(char* command);

extern int valid_id(node* mega_list, int list_id);

extern void print_node(node* node);

extern int mtll_create(node** mega_list, int size, int new_list_id);

extern void mtll_free(node *head);

extern void mtll_free_all(node* mega_list);

extern void mtll_view(node* mega_list, int index, printMode mode, int mega_size);

extern void mtll_view_all(node **mega_list, int mega_size);

extern int mtll_remove(node **mega_list, int list_id, int mega_size);

extern void mtll_insert(node **mega_list, int list_id, int index, int mega_size, char* data); 

extern void mtll_delete(node *mega_list, int list_id, int index, int mega_size);

#endif