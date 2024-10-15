#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define LINE 80 /* The maximum length command */

/*Ruslan Shikhhamzayev        CWID:12101982
Part 1
Project 2*/

char history[10][LINE];
int curCommand = 0;

void printHistory()
{
    for (int i = 0; i < 10 && i < curCommand; i++)
    {
        printf("%d %s\n", curCommand - i, history[(curCommand - i - 1) % 10]);
    }
}

void addCommand(char *command)
{
    strcpy(history[curCommand % 10], command);
    curCommand++;
}

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

        if (strcmp(input, "history") == 0)
        {
            printHistory();
            continue;
        }

        if (input[0] == '!')
        {
            if (input[1] == '!')
            {
                // entered !!
                if (curCommand == 0)
                {
                    printf("No commands in history.\n");
                    continue;
                }
                strcpy(input, history[(curCommand - 1) % 10]);
                printf("%s\n", input);
            }
            else
            {
                // entered !N
                int commandNumber;
                sscanf(input, "!%d", &commandNumber);
                if (commandNumber > curCommand || commandNumber < 1 || commandNumber < curCommand - 9)
                {
                    printf("No such command in history.\n");
                    continue;
                }
                strcpy(input, history[(commandNumber - 1) % 10]);
                printf("%s\n", input);
            }
        }

        // add input to history
        if (strcmp(input, "") != 0)
            addCommand(input);

        int i = 0;
        char *t = strtok(input, " ");
        while (t != NULL)
        {
            args[i] = t;
            i++;
            t = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (i > 0 && strcmp(args[i - 1], "&") == 0)
        {
            background = 1;
            args[i - 1] = NULL;
        }

        pid_t pidChild = fork();

        if (pidChild < 0) // error
        {
            perror("Fork failed");
            exit(1);
        }
        else if (pidChild == 0) // child
        {
            if (execvp(args[0], args) < 0)
            {
                perror("Execution failed");
                exit(1);
            }
        }
        else // parent
        {
            if (!background)
            {
                waitpid(pidChild, NULL, 0);
            }
        }
    }
    return 0;
}
