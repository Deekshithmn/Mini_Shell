#include"main.h"

int flag = 0;

void execute_internal_commands(char *input_string)
{  
    if(strcmp(input_string, "exit") == 0)
    {
        exit(1);
    }
    else if(strcmp(input_string, "pwd") == 0)// updated 
    {
        char buf[100];
       char *res=  getcwd(buf, 100);
       if(res == NULL)
       {
            if(errno == ERANGE)
            {
                char buf1[300];
                res = getcwd(buf1, 300);
                printf("%s\n",res);   
            }
       }
        printf("%s\n",buf);
    }
    else if(strncmp(input_string, "cd" , 2) == 0)
    {
        //printf("%c",input_string[3]);       
        if(chdir(&input_string[3]) == -1)
        {
            perror("cd");
        }
    }
    else if(strcmp(input_string, "echo $SHELL") == 0) //home directory
    {
        char *ret = getenv("SHELL");
        printf("%s\n",ret);
    }  
    else if(strcmp(input_string, "echo $$") == 0) //pid value
    {
        pid_t pid = getpid();
        printf("%d\n",pid);
    } 
    else if(strncmp(input_string, "echo $?",7) == 0)
    {
        printf("%d\n",WEXITSTATUS(status));
    }
    else if(strcmp(input_string, "jobs") == 0)
    {
        print_list(head);
    }
    else if(strcmp(input_string, "fg") == 0)
    {
        
        if(head == NULL)
        {
            printf("bash: fg: current: no such job\n");
        }
        else
        {
            kill(head->pid,SIGCONT);
            flag = 0;
            printf("%s\n", head->command);
            waitpid(head->pid,&status, WUNTRACED);
            if(WIFEXITED(status) == 1)
            {
                delete_at_first(&head);
            }
        }
        //print_list(head);
    }
    else if (strcmp(input_string, "bg") == 0)
    {
        flag = 1;
        
        if (head == NULL)
        {
            printf("bash: bg: current: no such job\n");
        }
        else
        {
            kill(head->pid, SIGCONT);
            printf("%s &\n", head->command);
            signal(SIGCHLD, signal_handler);
           // printf("[%d] %d resumed in background: %s\n", 1, head->pid, head->command);
        }
    }
}


// echo $? -> last exicuted process exit status