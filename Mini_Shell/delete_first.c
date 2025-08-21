#include "main.h"

int delete_at_first(Slist **head)
{
    if(*head == NULL)
    {
        return FAILURE;
    }
    Slist *temp = *head;
    *head = temp -> link ;
    free(temp);
    return SUCCESS;
}
