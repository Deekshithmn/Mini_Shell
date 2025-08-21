#include "main.h"

// convert input_string 1D array int 2D array;
void execute_external_commands(char *input_string)
{
    //char buf[25];
    int i = 0;//j = 0, index = 0;
    int pipe_flag = 0;
    char *token = strtok(input_string, " ");
    while (token != NULL)
    {
        array[i] = malloc(20);
        strcpy(array[i], token);
        token = strtok(NULL, " ");
        i++;
    }
    array[i] = NULL;


    // for (int k = 0; k < j; k++)
    // {
    //     // int res = strlen(array[k]);
    //     // array[k][res] = '\0';
    //     printf("exter_comm[%d] -> %s\n", k, array[k]);
    // }

    int c = 0;
    while (array[c] != NULL)
    {
        if (strcmp(array[c], "|") == 0)
        {
            pipe_flag = 1;
            break;
        }
        c++;
    }
    if (pipe_flag)
    {
        // printf("call the n_pip function\n");
        n_pipe();
        pipe_flag = 0;
    }
    else
    {
        if (execvp(array[0], array + 0) == -1)
        {
            //perror("execvp");
            exit(0);
        }
    }

    // for(int k = 0; k < j;k++)
    // {
    //     free(array[j]);
    // }
}
