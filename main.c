#include "include/minishell.h"

int     main(int ac, char **av, char **env)
{
    minishell_loop(env);
    return 0;
}