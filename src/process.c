#include "../include/minishell.h"

void    process_line()
{
    char **arg;
    char *tmp;
    int i;

    arg = ft_split(g_line, ' ');
    printf("----------\n");
    i = 0;
    while (arg[i])
    {
        printf("%s\n", arg[i]);
        i++;
    }
}