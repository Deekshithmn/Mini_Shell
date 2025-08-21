#include "main.h"

void signal_handler(int sig_num) // checking child is present or not
{
    if (sig_num == SIGINT)
    {
        if(pid == 0)
        { 
            printf("\n");
            printf(ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET, prompt);
           // pid = 0;
            fflush(stdout);
        }
    }
    else if(sig_num == SIGTSTP)
    {
       if(pid == 0)
        {
            if(input_string[0] == '\0')
            {
                printf("\n");
                printf(ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET, prompt);
                //pid = 0;
                fflush(stdout); 
            }
        }
        else
        {
            insert_at_first(&head, pid ,input_string);
        }

    }
    else if(sig_num == SIGCHLD)
    {
       //while( waitpid(-1, &status, WNOHANG)> 0);
       waitpid(-1, &status, WNOHANG);
       if(WIFEXITED(status) == 1)
       {
        flag = 0;
        delete_at_first(&head);
       }

    }
}