#include "../include/minishell.h"

void    readline()
{
    read(0, g_line, 1000);
}