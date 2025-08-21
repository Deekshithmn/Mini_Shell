#include "main.h"

char prompt[25] ="minishell@deekshith$";
char input_string[50];
int pid;
int status;
Slist *head = NULL;
char *array[50];
int main()
{
    system("clear");
    scan_input(prompt,input_string);
}

