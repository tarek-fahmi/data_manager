#ifndef HELPERS_H
#define HELPERS_H

#include "mtll.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int get_list_id(node *mega_node);

int has_reference(node *mega_list, int list_id);

int get_list_size(node *head);

int valid_id(node *mega_list, int list_id);

void invalid_command(char *command);

node *find_sublist(node *mega_list, int list_id);

void update_nestness(node *sublist_branch);

void print_node(node *element);

void print_node_type(node *node);

void mtll_print_list(node *head, printMode mode);

void recap(node *sublist_branch);

void free_node(node *Node);

#endif