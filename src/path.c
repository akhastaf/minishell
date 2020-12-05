#include "../include/minishell.h"


char *ft_getpath(char *file)
{
    struct stat sb;
    char **path;
    char *tmp;
    char *filepath;
    char *pathenv;
    int i;

    i = 0;
    pathenv = ft_getenv("PATH");
    path = ft_split(pathenv, ':');

    if (!stat(file, &sb) || ft_isbuiltins(file))
        return (ft_strdup(file));
    while (path[i])
    {
        filepath = ft_strappend(path[i], '/');
        tmp = filepath;
        filepath = ft_strjoin(filepath, file);
        free(tmp);
        if (!stat(filepath, &sb))
            return filepath;
        free(filepath);
        i++;
    }
    return (ft_strdup(file));
}