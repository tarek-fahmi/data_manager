#include "mtll.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH (128)

void execute_command(char *command, node **mega_list, int *new_list_id, int *available_lists) {
    int list_id;
    int index;
    char* data;

    if (strncmp(command, "VIEW", 4) == 0) {
        if (strcmp(command, "VIEW ALL") == 0) {
            mtll_view_all(mega_list, *available_lists);
        }else {
            if (sscanf(command, "VIEW %d", &list_id) == 1 && valid_id(*mega_list, list_id)) {
                mtll_view(*mega_list, list_id, 0, *available_lists);
            } else {
                invalid_command("VIEW");
            }
        }
    } else if (strncmp(command, "REMOVE", 6) == 0) {
        if (sscanf(command, "REMOVE %d", &list_id) == 1 ) {
            mtll_remove(mega_list, list_id, *available_lists);
            (*available_lists)--;
        } else {
            invalid_command("REMOVE");
        }

    } else if (strncmp(command, "NEW", 3) == 0) {
        if (sscanf(command, "NEW %d", &index) == 1 && index >= 0) {
            mtll_create(mega_list, index, *new_list_id);
            (*new_list_id)++;
            (*available_lists)++;
            printf("NEXT ID:%d, EXISTING LISTS:%d\n", *new_list_id, *available_lists);
        }else{
            invalid_command("NEW");
        }
    }else if((strncmp(command, "TYPE", 4) == 0)){
        if (sscanf(command, "TYPE %d", &list_id) == 1 && valid_id(*mega_list, list_id)) {
            mtll_view(*mega_list, list_id, 1, *available_lists);
        }else{
            invalid_command("TYPE");
        }
    }else if((strncmp(command, "INSERT", 6) == 0)){
        if (sscanf(command, "INSERT %d %d %s", &list_id, &index, data) == 3 && valid_id(*mega_list, list_id)) {
            mtll_insert(*mega_list, list_id, 1, *available_lists);
        }else{
            invalid_command("INSERT");
        }
    }else if((strncmp(command, "DELETE", 6) == 0)){
        if (sscanf(command, "DELETE %d %d", &list_id, &index) == 2 && valid_id(*mega_list, list_id)) {
            mtll_delete(*mega_list, list_id, index, *available_lists);
        }else{
            invalid_command("DELETE UPPER");
        }
    }
     else {
        invalid_command("INPUT");
    }
}

int main(int argc, char **argv) {
    char buffer[MAX_COMMAND_LENGTH];
    int new_list_id = 1;
    int available_lists = 0;

    printf("NEXT ID:%d, EXISTING LISTS:%d\n", new_list_id, available_lists);

    node *mega_list = NULL; // Initialize mega_list to NULL

    while (1) {
        fgets(buffer, sizeof(buffer), stdin);

        // Remove trailing newline character
        if (strlen(buffer) > 0 && buffer[strlen(buffer) - 1] == '\n') {
            buffer[strlen(buffer) - 1] = '\0';
        }

        // Execute the command.
        execute_command(buffer, &mega_list, &new_list_id, &available_lists);
    }

    return 0;
}
