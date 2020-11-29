#include "../include/minishell.h"

char    *ft_getenv(char **env, char *var)
{
    int i;
    int j;

    i = 0;
    while (env[i])
    {
        j = 0;
        while (var[j])
        {
            if (env[i][j] == 0 || var[j] != env[i][j])
                break;
            j++;
        }
        if (j == ft_strlen(var))
                return env[i] + j + 1;
        
        i++;
    }
    return NULL;
}

int     ft_env(char **arg)
{
    int i;
    
    i = 0;
    while (g_sh.env[i])
    {
        write(1, g_sh.env[i], ft_strlen(g_sh.env[i]));
        write(1, "\n", 1);
        i++;
    }
    return 1;
}