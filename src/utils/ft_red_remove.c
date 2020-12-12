#include "../../include/minishell.h"

void    ft_red_remove(t_red *red)
{
    if (red->type)
        free(red->type);
    if (red->file)
        free(red->file);
    free(red);
    red = NULL;
}