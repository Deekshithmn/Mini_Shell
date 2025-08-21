#include "main.h"


//extern char input_string[50];
void scan_input(char *prompt, char *input_string)
{
    extract_external_commands(external_commands);
    signal(SIGINT, signal_handler);
    signal(SIGTSTP, signal_handler);
    
    while (1)
    {
        printf(ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET, prompt);
        // fgets(input_string, 25, stdin);
        scanf("%[^\n]",input_string);
        //int ret = strlen(input_string);
        // fflush(stdout);
        //input_string[ret - 1] = '\0';
        // scanf("%[^\n]", input_string);
        getchar();

        // validate the input_string with PS1
        if (strstr(input_string, "PS1") == NULL) // if it is not (PS1)present
        {
            char *command = get_command(input_string);
            // printf("%s\n",command);

            int ret = check_command_type(command);
            //printf("%d\n", ret);

            if (ret == 1)
            {
                execute_internal_commands(input_string);
            }
            else if (ret == 2)
            {
                pid = fork();
                if(pid > 0)
                {
                    //wait(&status); //(it is not working if child is stoped)
                    waitpid(pid,&status,WUNTRACED);
                    pid = 0;
                }
                else if(pid == 0)
                { 
                    signal(SIGINT, SIG_DFL);
                    signal(SIGTSTP, SIG_DFL);
                    execute_external_commands(input_string);
                } 
            }
            else{
                printf("%s: command not found\n",input_string);

            }
        }
        else // if PS1 is present
        {
            // Check if space exists after PS1
            if (strchr(input_string, ' ') != NULL)
            {
                printf("INFO: Invalid command\n");
                printf("Enter the correct command\n");
            }
            else
            {
                strcpy(prompt, &input_string[4]);
                continue;
            }
        }
        // removing white space
        memset(input_string, '\0', sizeof(input_string));
    }
}

// to get the first word from the input string
char *get_command(char *input_string)
{
    static char command[20];
    int i = 0;
    while (input_string[i] != ' ' && input_string[i] != '\0')
    {
        command[i] = input_string[i];
        i++;
    }
    command[i] = '\0';
    // printf("%s",command);
    return command;
}

// create and stored into 2D array
void extract_external_commands(char **external_commands)
{
    int fd = open("external_comm.txt", O_RDONLY);

    if (fd == -1)
    {
        printf("ERROR: File is not open\n");
    }
    char buf[50];
    char ch;
    int i = 0, j = 0;
    while (read(fd, &ch, 1))
    {
        if (ch == '\n')
        {
            buf[i] = '\0';
            // printf("buffer-> %s",buf);
            external_commands[j] = calloc(1, sizeof(buf) + 1);
            strcpy(external_commands[j], buf);
            j++;
            i = 0;
        }
        else
        {
            buf[i] = ch;
            i++;
        }
    }
    external_commands[j] = NULL;
    // printf("external_comm-> %s\n",external_commands[0]);
    // for(int i = 0; i <= 152; i++)
    // {
    //     printf("external_comm[%d]-> %s\n",i,external_commands[i]);
    // }
}


