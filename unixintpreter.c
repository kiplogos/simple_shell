#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LEN 1024

void simple_shell()
{
	char input[MAX_LEN];

	 while (1) {
	     printf("$ ");
	     if (fgets(input, MAX_LEN, stdin) == NULL) {
	         printf("\n");
		 break;
	     }

	     // Remove the newline character from the input
	     // input[strcspn(input, "\n")] = 0;
	     
	     if (strlen(input) == 0) {
		 continue;
	     }

	     pid_t pid = fork();
	     if (pid == -1) {
		 perror("fork");
		 exit(1);
	     } else if (pid == 0) {
    	       if (execlp(input, input, (char *) NULL) == -1) {
		   perror("execlp");
		   exit(1);
	       }
	     } else {
		     int status;
		     waitpid(pid, &status, 0);
	     }
	 }
}

int main(void)
{
	simple_shell();
	return 0;
}
