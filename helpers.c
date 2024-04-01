#include "mtll.h"
#include "helpers.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

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

    // Search for sublist with ID.
    while (current != NULL)
    {
        // Return sublist if found.
        if (get_list_id(current) == list_id)
            return ((node *)current->data); 

        current = current->next; 
    }
    // Return NULL if not found.
    return NULL;
}

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
            sublist_branch->type = NEST; 
            return;
        }
        current = current->next; 
    }
    // If no nested content found, set type to list.
    sublist_branch->type = LIST;
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
        }
        current = current->next;
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
    }
    mtll_print_list(sublist_head, DATA);
    printf("\n");
    return;
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