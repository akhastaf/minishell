#include "../../include/minishell.h"

int     builtins_env(char **arg)
{
    int i;
    char *lstcmd;
    int l;
    
    i = 1;
    lstcmd = ft_getenv("_");
    if (lstcmd)
        ft_envremove("_");
    free(lstcmd);
    lstcmd = ft_getpath(ft_strdup("ENV"));
    l = ft_strlen(lstcmd);
    while (i < 4)
    {
        lstcmd[l - i] = ft_tolower(lstcmd[l - i]);
        i++;
    }
    ft_setenv("_", lstcmd);
    free(lstcmd);
    i = 0;
    while (g_sh.env[i])
    {
        if (ft_strchr(g_sh.env[i], '='))
            ft_putendl_fd(g_sh.env[i], 1); 
        i++;
    }
    return 0;
}