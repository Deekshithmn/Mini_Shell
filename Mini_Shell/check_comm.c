#include "main.h"

//extern char *external_commands[200];
int check_command_type(char *command)
{
    char *builtins[] = {"echo", "printf", "read", "cd", "pwd", "pushd", "popd", "dirs", "let", "eval",
						"set", "unset", "export", "declare", "typeset", "readonly", "getopts", "source",
						"exit", "exec", "shopt", "caller", "true", "type", "hash", "bind", "help","jobs", "fg","bg", NULL};
    
    for(int i = 0; builtins[i] != NULL; i++)
    {
        if(strcmp(builtins[i], command) == 0)
        {
            //printf("matching builtin\n");
            return 1;
        }
    }

    for(int i = 0; external_commands[i] != NULL; i++)
    {
        if(strncmp(external_commands[i], command,strlen(command)) == 0)
        {
            //printf("matching external\n");
            return 2;
        }
    }

    //printf("NOT Matching\n");
    return 3;
    

        
}