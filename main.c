#include "mtll.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_COMMAND_LENGTH (256)

// Function to cast a string to an integer.
// Description: Checks if the provided string can be cast to an integer.
// Parameters: string - string to be casted, number - pointer to store the integer value
// Returns: 1 if casting is successful, 0 otherwise
int cast_integer(char *string, int *number)
{
    // Check each character in the string
    for (int j = 0; string[j] != '\0'; j++)
    {
        if (!isdigit(string[j]) && string[j] != '-')
        {
            return 0;
        }
    }
    *number = atoi(string);
    return 1;
}

// Function to execute a command provided as input and perform corresponding operations on the mega list.
// Description: Parses the input command and executes corresponding operations on the mega list.
// Parameters: command - string representing the command to be executed,
//             mega_list - pointer to the pointer to the mega list,
//             new_list_id - pointer to the integer storing the ID for new lists,
//             available_lists - pointer to the integer storing the count of available lists
void execute_command(char *command, node **mega_list, int *new_list_id, int *available_lists)
{
    int list_id, index;
    char list_id_str[8], index_str[8], data[MAX_COMMAND_LENGTH];

    // VIEW command
    if (strncmp(command, "VIEW", 4) == 0)
    {
        // VIEW ALL
        if (strcmp(command, "VIEW ALL") == 0)
        {
            mtll_view_all(mega_list, *available_lists);
        }
        // VIEW NESTED
        else if (sscanf(command, "VIEW-NESTED %s", list_id_str) == 1 && cast_integer(list_id_str, &list_id) && valid_id(*mega_list, list_id))
        {
            mtll_view(*mega_list, list_id, NESTED, *available_lists);
        }
        // VIEW DATA
        else if (sscanf(command, "VIEW %s", list_id_str) == 1 && cast_integer(list_id_str, &list_id) && valid_id(*mega_list, list_id))
        {
            mtll_view(*mega_list, list_id, DATA, *available_lists);
        }
        else
        {
            invalid_command("VIEW");
        }
    }
    // REMOVE command
    else if (strncmp(command, "REMOVE", 6) == 0)
    {
        // REMOVE LIST
        if (sscanf(command, "REMOVE %s", list_id_str) == 1 && cast_integer(list_id_str, &list_id) && valid_id(*mega_list, list_id))
        {
            (*available_lists) -= mtll_remove(mega_list, list_id, *available_lists);
        }
        else
        {
            invalid_command("REMOVE");
        }
    }
    // NEW command
    else if (strncmp(command, "NEW", 3) == 0)
    {
        // NEW LIST
        if (sscanf(command, "NEW %s", index_str) == 1 && cast_integer(index_str, &index) && index >= 0)
        {
            if (mtll_create(mega_list, index, *new_list_id))
            {
                (*new_list_id)++;
                (*available_lists)++;
            }
        }
        else
        {
            invalid_command("NEW");
        }
    }
    // TYPE command
    else if ((strncmp(command, "TYPE", 4) == 0))
    {
        // TYPE LIST
        if (sscanf(command, "TYPE %s", list_id_str) == 1 && cast_integer(list_id_str, &list_id) && valid_id(*mega_list, list_id))
        {
            mtll_view(*mega_list, list_id, 1, *available_lists);
        }
        else
        {
            invalid_command("TYPE");
        }
    }
    // INSERT command
    else if ((strncmp(command, "INSERT", 6) == 0))
    {
        // INSERT DATA
        if (sscanf(command, "INSERT %s %s", list_id_str, index_str) == 2 &&
            cast_integer(list_id_str, &list_id) && cast_integer(index_str, &index) &&
            valid_id(*mega_list, list_id))
        {
            list_id = atoi(list_id_str);
            index = atoi(index_str);
            char *data_start = command + strlen("INSERT") + strlen(list_id_str) + strlen(index_str) + 3; 
            mtll_insert(mega_list, list_id, index, *available_lists, data_start);
        }
        else
        {
            invalid_command("INSERT");
        }
    }
    // DELETE command
    else if ((strncmp(command, "DELETE", 6) == 0))
    {
        // DELETE DATA
        if (sscanf(command, "DELETE %s %s%[^\n]", list_id_str, index_str, data) == 2 && cast_integer(list_id_str, &list_id) && cast_integer(index_str, &index) && valid_id(*mega_list, list_id))
        {
            list_id = atoi(list_id_str);
            index = atoi(index_str);
            mtll_delete(*mega_list, list_id, index, *available_lists);
        }
        else
        {
            invalid_command("DELETE");
        }
    }
    else
    {
        invalid_command("INPUT");
    }
}

// Main function to execute the program.
// Description: Reads input commands from stdin, executes corresponding operations, and manages memory.
int main(int argc, char **argv)
{
    char *buffer = NULL;
    size_t buffer_size = 0;
    int new_list_id = 0;
    int available_lists = 0;

    node *mega_list = NULL;

    while (getline(&buffer, &buffer_size, stdin) != -1)
    {
        // Remove trailing newline character
        size_t length = strlen(buffer);
        if (length > 0 && buffer[length - 1] == '\n')
        {
            buffer[length - 1] = '\0';
        }

        execute_command(buffer, &mega_list, &new_list_id, &available_lists);
    }
    mtll_free_all(mega_list);
    free(buffer);

    return 0;
}