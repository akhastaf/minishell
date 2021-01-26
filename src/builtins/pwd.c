#include "../../include/minishell.h"

int     builtins_pwd(char **arg)
{
    char    *pwd;

    pwd = getcwd(NULL, 0);
    if (!pwd)
        pwd = ft_getenv("PWD");
    ft_putendl_fd(pwd, 1);
    return 0;
}