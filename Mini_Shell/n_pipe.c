#include "main.h"

void n_pipe()
{ 
    int cmd_pos[25];
    int i = 1;
    int cmd_count=1;
    int pipe_count =0;
    cmd_pos[0] = 0;
    while(array[i] != NULL )
    {
        if(strcmp(array[i] , "|" ) == 0)
        {
            array[i] = NULL;
            pipe_count++;
            cmd_pos[cmd_count++] = i + 1;
        }
        // else if(array[i - 1] == NULL)
        // {
        //     cmd_pos[cmd_count++] = i;
        // }
        i++;
    }
    
//    printf("cmd_count-> %d\n",cmd_count);
//     for(int i = 0;i< cmd_count; i++)
//     {
//         for(int j = cmd_pos[i]; argv[j] != NULL; j++)
//         {
//             printf("command[%d] ->[%d] ->> %s ",i + 1,j,argv[j]);

//         }
//         printf("\n");
//     }
    
    // if(pipe_count == 0)
    // {
    //     printf("ERROR: Pipe is not passed\n");
    //     exit(0);
    // }
    if(pipe_count == cmd_count)
    {
        exit(0);
    }
    
    int fd[2]; // one for write and another for read

    if(cmd_count != 0)
    {
        for(int i = 0; i< cmd_count; i++)
        {
            if(i < cmd_count -1)
            {
                if(pipe(fd) == -1)
                {
                    perror("pipe");
                    //return -1;
                }
            }

            pid_t pid = fork();
            if(pid > 0)
            {
                wait(NULL);
                if(i < cmd_count-1)
                {
                    close(fd[1]);
                    dup2(fd[0], 0);
                    close(fd[0]);
                }    
            }
            else if(pid == 0)
            {
                if(i < cmd_count -1)
                {
                    close(fd[0]);
                    dup2(fd[1],1);
                    //close(fd[1]);
                }
                execvp(array[cmd_pos[i]], array + cmd_pos[i]);
            }
            else{
                perror("fork\n");
            }

        }
    }
    exit(0);
}

