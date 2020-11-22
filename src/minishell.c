#include "../include/minishell.h"

void        minishell_loop(char **env)
{
    int status;

    status = 1;
    int i;
    i=0;
    char *pwd;
    while(status)
    {
        //write()
        while(env[i]) 
        {
            if (strnstr(env[i], "PWD=", strlen(env[i])))
            {
                pwd = strnstr(env[i], "PWD=", strlen(env[i]));
                break;
            }
            i++;
        }
        write(1, "\033[0;32m", 8);
        write(1, pwd + 4, strlen(pwd) - 4);
        write(1, "$> ", 3);
        write(1, "\033[0m", 5);
        readline();
        printf("%s", g_line);
        //process_line();
        //excute();
    }
}