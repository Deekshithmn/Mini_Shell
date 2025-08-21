#include "main.h"

int insert_at_first(Slist **head, int pid, char *command)
{
    Slist *new = malloc(sizeof(Slist));

    if (new == NULL)
        return FAILURE;

    new->pid = pid;
    strcpy(new->command, command);
    new->link = *head; 
    *head = new;

    return SUCCESS;
}

void print_list(Slist *head)
{
    if (head == NULL)
    {
        // printf("INFO :no stopped process \n");
        return;
    }

    int i = 1;
    int j= 1;
    while (head)
    {
        if(flag == 1 && j == 1)
        {
            printf("[%d]  Running    %s\n", i, head->command);
        }
        else
            printf("[%d]  Stopped    %s\n", i, head->command);
        head = head->link;
        i++;
        j = 0;
    }
}
