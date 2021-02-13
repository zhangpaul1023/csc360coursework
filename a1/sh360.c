/*appendix A program.
 * CSC 360, Spring 2021
 *  *
 *   * This shows how a simple loop obtaining input from the user can
 *    * be written. Notice the use of "fflush".
 *     *
 *      * If "mittens" is entered, then the shell terminates.
 *       */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>
#define MAX_INPUT_LINE 100
#define MAX_NUM_TOKENS 8 //include the PP or OR. total is 7



void normal(char *token[], char path[], int num_tokens){
    int status;
    int pid, fd;
    char argsTemp[80];
    if (path[strlen(path) - 1] == '\n') {
        path[strlen(path) - 1] = '\0';
    }
    strcpy(argsTemp, path);
    strcat(argsTemp, "/");
    strcat(argsTemp, token[0]);
    char *args[3];
    char *envp[] = { 0 };
    if (num_tokens == 1){
        args[0] = argsTemp;
        args[1] = NULL;
        args[2] = 0;
    }
    if (num_tokens != 1){
        args[0] = argsTemp;
        args[1] = token[1];
        args[2] = 0;
    }
    if ((pid = fork()) == 0){
        execve(args[0], args, envp);
        printf("child: SHOULDN'T BE HERE.\n");
    }
    waitpid(pid, &status, 0);
}


void OR(char *token[], char path[], int num_tokens){
    int status;
    int pid, fd;
    char argsTemp[80];
    
    if (path[strlen(path) - 1] == '\n') {
        path[strlen(path) - 1] = '\0';
    }
    strcpy(argsTemp, path);
    strcat(argsTemp, "/");
    strcat(argsTemp, token[1]);
    char *args[3];
    if (strcmp(token[2], "->") == 0){
        args[0] = argsTemp;
        args[1] = NULL;
        args[2] = 0;
    }
    if (strcmp(token[2], "->") != 0){
        args[0] = argsTemp;
        args[1] = token[2];
        args[2] = 0;
    }
    char *envp[] = { 0 };
    if ((pid = fork()) == 0) {
	    if (token[num_tokens-1][strlen(token[num_tokens-1]) - 1] == '\n') {
	        token[num_tokens-1][strlen(token[num_tokens-1]) - 1] = '\0';
	    }
        fd = open(token[num_tokens-1], O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
        if (fd == -1) {
            fprintf(stderr, "cannot open %s for writing\n", token[num_tokens-1]);
            exit(1);
        }
	    dup2(fd, 1);
	    dup2(fd, 2);
        execve(args[0], args, envp);
        printf("child: SHOULDN'T BE HERE.\n");
    }
    waitpid(pid, &status, 0);
}


void exec1(char *token1, char *token2, char path[], int *pipe1, int *pipe2) {
// input from stdin (already done)
  // output to pipe1
    if (path[strlen(path) - 1] == '\n') {
        path[strlen(path) - 1] = '\0';
    }
    if (token1[strlen(token1) - 1] == '\n') {
        token1[strlen(token1) - 1] = '\0';
    }
    if (token2[strlen(token2) - 1] == '\n') {
        token2[strlen(token2) - 1] = '\0';
    }
    char argsTemp[80];
    strcpy(argsTemp, path);
    strcat(argsTemp, "/");
    strcat(argsTemp, token1);
  // output to pipe1
    dup2(pipe1[1], 1);
  // set args and envp
    char *args[] = {argsTemp, token2, 0};
    char *envp[] = { 0 };
  // close fds
    close(pipe1[0]);
    close(pipe1[1]);
  // exec
    execve(args[0], args, envp);
  // exec didn't work, exit
    fprintf(stdout, "Error: bad exec ps");
    exit(1);
}

void exec1for2cmd(char *token1, char *token2, char path[], int *pipe1){
    if (path[strlen(path) - 1] == '\n') {
        path[strlen(path) - 1] = '\0';
    }
    if (token1[strlen(token1) - 1] == '\n') {
        token1[strlen(token1) - 1] = '\0';
    }
    if (token2[strlen(token2) - 1] == '\n') {
        token2[strlen(token2) - 1] = '\0';
    }
    char argsTemp[80];
    strcpy(argsTemp, path);
    strcat(argsTemp, "/");
    strcat(argsTemp, token1);
    dup2(pipe1[1], 1);
    char *args[] = {argsTemp, token2, 0};
    char *envp[] = { 0 };
    close(pipe1[0]);
    execve(args[0], args, envp);
    printf("child (head): SHOULDN'T BE HERE.\n");
}

void exec2(char *token1, char *token2, char path[], int *pipe1, int *pipe2) {
    if (path[strlen(path) - 1] == '\n') {
        path[strlen(path) - 1] = '\0';
    }
    if (token1[strlen(token1) - 1] == '\n') {
        token1[strlen(token1) - 1] = '\0';
    }
    if (token2[strlen(token2) - 1] == '\n') {
        token2[strlen(token2) - 1] = '\0';
    }
    char argsTemp[80];
    strcpy(argsTemp, path);
    strcat(argsTemp, "/");
    strcat(argsTemp, token1);
  // input from pipe1
    dup2(pipe1[0], 0);
  // output to pipe2
    dup2(pipe2[1], 1);
  // set args and envp
    char *args[] = {argsTemp, token2, 0};
    char *envp[] = { 0 };
  // close fds
    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[0]);
    close(pipe2[1]);
  // exec
    execve(args[0], args, envp);
  // exec didn't work, exit
    fprintf(stdout, "Error: bad exec ps");
    exit(1);
}

void exec2for2cmd(char *token1, char *token2, char path[], int *pipe1){
    if (path[strlen(path) - 1] == '\n') {
        path[strlen(path) - 1] = '\0';
    }
    if (token1[strlen(token1) - 1] == '\n') {
        token1[strlen(token1) - 1] = '\0';
    }
    if (token2[strlen(token2) - 1] == '\n') {
        token2[strlen(token2) - 1] = '\0';
    }
    char argsTemp[80];
    strcpy(argsTemp, path);
    strcat(argsTemp, "/");
    strcat(argsTemp, token1);
    dup2(pipe1[0], 0);
    char *args[] = {argsTemp, token2, 0};
    char *envp[] = { 0 };
    close(pipe1[1]);
    execve(args[0], args, envp);
    printf("child (head): SHOULDN'T BE HERE.\n");
}

void exec3(char *token1, char *token2, char path[], int *pipe1, int *pipe2) {
    if (path[strlen(path) - 1] == '\n') {
        path[strlen(path) - 1] = '\0';
    }
    if (token1[strlen(token1) - 1] == '\n') {
        token1[strlen(token1) - 1] = '\0';
    }
    if (token2[strlen(token2) - 1] == '\n') {
        token2[strlen(token2) - 1] = '\0';
    }
    char argsTemp[80];
    strcpy(argsTemp, path);
    strcat(argsTemp, "/");
    strcat(argsTemp, token1);
  // input from pipe2
    dup2(pipe2[0], 0);
  // output to stdout (already done)
  // set args and envp
    char *args[] = {argsTemp, token2, 0};
    char *envp[] = { 0 };
  // close fds
    close(pipe2[0]);
    close(pipe2[1]);
  // exec
    execve(args[0], args, envp);
  // exec didn't work, exit
    fprintf(stdout, "Error: bad exec ps");
    exit(1);
}



void PP(char *token[], char path[], int num_tokens){
    int numOfArror = 0;
    char argsTemp[80];
    int x = 0;
    while (x < num_tokens){
        if (strcmp(token[x], "->") == 0){
            numOfArror++;
        }
        x++;
    }
    if (numOfArror == 1){
        int pid;
        int pipe1[2];
        if (pipe(pipe1) == -1) {
            fprintf(stdout, "Error: bad pipe1");
            exit(1);
        }
        if ((pid = fork()) == -1) {
            fprintf(stdout, "Error: bad fork1");
            exit(1);
        }
        else if (pid == 0) {
            exec1for2cmd(token[1], token[2], path, pipe1);
        }
        if ((pid = fork()) == -1) {
            fprintf(stdout, "Error: bad fork2");
            exit(1);
        }
        else if (pid == 0) {
            exec2for2cmd(token[4], token[5], path, pipe1);
        }
        close(pipe1[0]);
        close(pipe1[1]);
    }
    if (numOfArror == 2){
        int pid;
        int pipe1[2];
        int pipe2[2]; 
        // create pipe1
        if (pipe(pipe1) == -1) {
            fprintf(stdout, "Error: bad pipe1");
            exit(1);
        }

      // fork (ps aux)
        if ((pid = fork()) == -1) {
            fprintf(stdout, "Error: bad fork1");
            exit(1);
        }
        else if (pid == 0) {
            exec1(token[1], token[2], path, pipe1, pipe2);
        }
      // parent

      // create pipe2
        if (pipe(pipe2) == -1) {
            fprintf(stdout, "Error: bad pipe2");
            exit(1);
        }

        if ((pid = fork()) == -1) {
            fprintf(stdout, "Error: bad fork2");
            exit(1);
        }
        else if (pid == 0) {

            exec2(token[4], token[5], path, pipe1, pipe2);
        }
      // parent

      // close unused fds
        close(pipe1[0]);
        close(pipe1[1]);

      // fork (grep sbin)
        if ((pid = fork()) == -1) {
            fprintf(stdout, "Error: bad fork3");
            exit(1);
        }
        else if (pid == 0) {
            exec3(token[7], token[8], path, pipe1, pipe2);
        }
    }
}

int main(int argc, char *argv[]) {
    char input[MAX_INPUT_LINE];
    int returnNum, i;
    char *t;
    char *token[MAX_NUM_TOKENS];
    int num_tokens;
    char str[MAX_INPUT_LINE];
    char path[10][MAX_INPUT_LINE];
    char argsTemp[80];
    FILE *fp;
    fp = fopen(".sh360rc", "r");
    fgets(str, MAX_INPUT_LINE, (FILE*) fp);
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }
    i = 0;
    while (fgets(path[i], MAX_INPUT_LINE, fp) && i < 10){
	   i++;
    }
    fclose(fp);

    for(;;) {
	    printf("%s", str);
        returnNum = 0;
	    fgets(input, MAX_INPUT_LINE, stdin);
        if (input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] = '\0';
        }
        if (strcmp(input, "exit") != 0){
            bool pathAccess = false;
	        num_tokens = 0;
	        t = strtok(input, " ");
	        while (t != NULL && num_tokens < MAX_NUM_TOKENS) {
	            token[num_tokens] = t;
	            num_tokens++;
	            t = strtok(NULL, " ");
	        }
	        int n = 0;
	        while (returnNum != 1){
                if ((strcmp(token[0],"OR") == 0) || (strcmp(token[0],"PP") == 0)){
                    if (path[n][strlen(path[n]) - 1] == '\n') {
                        path[n][strlen(path[n]) - 1] = '\0';
                    }
                    strcpy(argsTemp, path[n]);
                    strcat(argsTemp, "/");
                    strcat(argsTemp, token[1]);
    	            if ((access(argsTemp, R_OK)) == 0){
    		            returnNum = 1;
                        pathAccess = true;
    	            }
    	            if ((access(argsTemp, R_OK)) != 0){
    	                n = n + 1;
    	            }
                    if (n == 10){
                        fprintf(stdout, "Error: Can't find the path.\n");
                        returnNum = 1;
                    }
                }
                else{
                    if (path[n][strlen(path[n]) - 1] == '\n') {
                        path[n][strlen(path[n]) - 1] = '\0';
                    }
                    strcpy(argsTemp, path[n]);
                    strcat(argsTemp, "/");
                    strcat(argsTemp, token[0]);
                    if ((access(argsTemp, R_OK)) == 0){
                        returnNum = 1;
                        pathAccess = true;
                    }
                    if ((access(argsTemp, R_OK)) != 0){
                        n = n + 1;
                    }
                    if (n == 10){
                        fprintf(stdout, "Error: Can't find the path.\n");
                        returnNum = 1;
                    }
                }
	        }
            if (pathAccess){
                if (strcmp(token[0],"OR") == 0){
                    OR(token, path[n], num_tokens);
                }
                else if (strcmp(token[0],"PP") == 0){
                    PP(token, path[n], num_tokens);
                }
                else{
                    normal(token, path[n], num_tokens);
                }
            }
            returnNum = 0;
        }

        if (strcmp(input, "exit") == 0) {
            exit(0);
        }
         
// 	/*
// 	if (token[] == \"PP\"){
// 	    char argsTemp[];
// 	    strcpy(argsTemp, );
// 	    strcat(argsTemp, token[]);
// 	    char *args[] = { argsTemp, token[], };
// 	    char *envp[] = {  };
// 	}
// 	*/
        
        
        
    }
 }
