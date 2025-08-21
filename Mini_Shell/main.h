#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
 
typedef struct node{
    int pid;
    char command[25];
    struct node *link;
}Slist;
#define FAILURE     0
#define SUCCESS     1
#define BUILTIN		1
#define EXTERNAL	2
#define NO_COMMAND  3

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


void scan_input(char *prompt, char *input_string);
char *get_command(char *input_string); // to get the first word

void copy_change(char *prompt, char *input_string);

int check_command_type(char *command);
//void echo(char *input_string, int status);
void execute_internal_commands(char *input_string);
void execute_external_commands(char *input_string);
void signal_handler(int sig_num);
void extract_external_commands(char **external_commands);
void n_pipe();


char *external_commands[200];
extern char prompt[25];
extern int status;
extern int pid;
extern char input_string[50];
extern  int flag;
extern char *array[50];


extern Slist *head;
int insert_at_first(Slist **head, int pid ,char *command );
void print_list(Slist *head);
int delete_at_first(Slist **);


#endif
