#include "../../include/minishell.h"

int     ft_is_space(char c)
{
    if (c == ' ' || c == '\t')
        return 1;
    return 0;
}