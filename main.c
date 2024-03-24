#include "mtll.h"

#include <stdio.h>

#define MAX_COMMAND_LENGTH (128)

void execute_command(char *command, node **mega_list, int *new_list_id, int *available_lists)
{

    int index;

    if (strncmp(command, "VIEW", 4) == 0){
        if (sscanf(command, "REMOVE %d", &index) == 1){
                mtll_view(mega_list, index);
        }else{
            invalid_command(command);
        }
        
    }else if (strcmp(command, "VIEW ALL") == 0){
        
        mtll_view_all(&mega_list, available_lists);

    }else if (strncmp(command, "REMOVE", 6) == 0){
        if (sscanf(command, "REMOVE %d", &index) == 1 && index >= 0){
                mtll_remove(&mega_list, index);
                *available_lists--;
            }
        else{
            invalid_command(command);
        }

    } else if (strncmp(command, "NEW", 3) == 0) {
        if (sscanf(command, "NEW %d", &index) == 1 && index >= 0){
            
            
            mtll_create(&mega_list, index, new_list_id);
            *new_list_id ++;
            *available_lists++;
        } else{
            invalid_command(command);
        }
    }
    return;
}

int main(int argc, char **argv) {

    // TODO:

    // You should do general input / output management here.

    char buffer[MAX_COMMAND_LENGTH];
    int new_list_id = 1;
    int available_lists = 0;

    node *mega_list = NULL;

        while (1){
        fgets(buffer, sizeof(buffer), stdin);

        // Remove trailing newline character

        if (strlen(buffer) > 0 && buffer[strlen(buffer) - 1] == '\n'){
            buffer[strlen(buffer) - 1] = '\0';
        }

        // Execute the command.
        execute_command(buffer, &mega_list, &new_list_id, &available_lists);
    }

    return 0;
}