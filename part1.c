#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define LINE 80 /* Max line length */

int main(void)
{
    char *args[LINE / 2 + 1]; // command line arguments
    char input[LINE];         // user input
    pid_t pidParent = getpid();
    int should_run = 1; // exit command
    int background = 0; // background flag

    while (should_run)
    {
        background = 0;
        printf("Shikhhamzayev%d>", pidParent);
        fflush(stdout);

        fgets(input, LINE, stdin);

        input[strcspn(input, "\n")] = 0;

        int size = 0;
        char *t = strtok(input, " ");
        while (t != NULL)
        {
            args[size] = t;
            size++;
            t = strtok(NULL, " ");
        }
        args[size] = NULL;

        if (size > 0 && strcmp(args[size - 1], "&") == 0)
        {
            background = 1;
            args[size - 1] = NULL;
        }

        pid_t pidChild = fork();

        if (pidChild < 0)
        {
            perror("Fork failed");
            exit(1);
        }
        else if (pidChild == 0)
        {
            if (execvp(args[0], args) < 0)
            {
                perror("Execution failed");
                exit(1);
            }
        }
        else
        {
            if (!background)
            {
                waitpid(pidChild, NULL, 0);
            }
        }
    }
    return 0;
}
