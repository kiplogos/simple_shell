#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

int main() {
    char user_input[MAX_COMMAND_LENGTH];

    while(1) {
        printf("$ ");
        fgets(user_input, MAX_COMMAND_LENGTH, stdin); // read input from user
        user_input[strcspn(user_input, "\n")] = '\0'; // remove trailing newline character

        if (strlen(user_input) == 0) {
            continue; // if input is empty, prompt again
        }

        pid_t pid = fork(); // create a new process

        if (pid < 0) {
            printf("Error: fork failed\n");
            exit(1);
        }

        if (pid == 0) { // child process
            execlp(user_input, user_input, (char *) NULL); // execute command
            printf("Error: command not found\n"); // if exec returns, command failed
            exit(1);
        }

        else { // parent process
            int status;
            waitpid(pid, &status, 0); // wait for child process to finish
        }
    }

    return 0;
}

