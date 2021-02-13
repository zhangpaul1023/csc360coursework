/*
 * Appendix A program.
 * CSC 360, Spring 2021
 *
 * This shows how a simple loop obtaining input from the user can
 * be written. Notice the use of "fflush".
 *
 * If "mittens" is entered, then the shell terminates.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LINE 100


int main(int argc, char *argv[]) {
    char input[MAX_INPUT_LINE];
    int  line_len;
    for(;;) {
        fprintf(stdout, "> ");
        fflush(stdout);
        fgets(input, MAX_INPUT_LINE, stdin);
        if (input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] = '\0';
        }

        line_len = strlen(input); 
        fprintf(stdout, "echo: line was %d chars long\n", line_len);

        if (strcmp(input, "mittens") == 0) {
            exit(0);
        }
    }
}
char pathOfPP[MAX_INPUT_SIZE];
char temp_command[MAX_INPUT_SIZE];
int i, pid, status;
int path_found = 0;

memset(temp_path, 0, MAX_INPUT_SIZE);
memset(temp_command, 0, MAX_INPUT_SIZE);

strncpy(temp_command, arg->commands[0], MAX_INPUT_SIZE);

for (i = 0; i < paths->path_count ; i++){
    strncpy(pathOfPP, paths->path_names[i], MAX_INPUT_SIZE); //put path name into buffer
    strcat(pathOfPP, temp_command); //put command name behind path name
    if (access(pathOfPP, F_OK|X_OK) == 0){ //found a correct path, break the loop
        path_found = 1;
        break;
    }
}
if (!path_found){
    printf("Error: binary of %s cannot be found or exectued.\n", temp_command);
    exit(-1);
}


char temp_path[3][MAX_INPUT_SIZE]; // 3 pointers to 3 paths repectively to head, mid, tail
char temp_command[MAX_INPUT_SIZE];
int i;
int current_command = 0;
int path_found[] = {0,0,0}; //same as temp_path
char pathOfPP[3];
for(i = 0; i < 3; i++){
    memset(temp_path[i], 0, MAX_INPUT_SIZE);
}

memset(temp_command, 0, MAX_INPUT_SIZE);

strncpy(temp_command, token[1], MAX_INPUT_SIZE);

for (current_command = 1; current_command < strlen(token); current_command++){ //loop for each command
    strncpy(temp_command, token[current_command], MAX_INPUT_SIZE);  //copy current command from commands

    for (i = 0; i < strlen(path) ; i++){ //use current command to find correct path

        strncpy(temp_path[current_command], path[i], MAX_INPUT_SIZE); //put path name into buffer
        strcat(temp_path[current_command], temp_command); //put command name behind path name
        if (access(temp_path[current_command], F_OK|X_OK) == 0){ //found a correct path, break the loop
            path_found[current_command] = 1;
            pathOfPP[current_command] = temp_path[current_command];
            break;
        }
    }
}