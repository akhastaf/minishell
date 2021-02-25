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
    if (ft_is_empty(file) || file[0] == '.' || ft_isbuiltins(file) || !pathenv || ft_strchr(file, '/'))
    {
        free(pathenv);
        return (file);
    }
    path = ft_split(pathenv, ":");
    free(pathenv);
    while (path[i])
    {
        filepath = ft_strjoin(path[i], "/");
        tmp = filepath;
        filepath = ft_strjoin(filepath, file);
        free(tmp);
        if (!stat(filepath, &sb))
        {
            free(file);
            ft_delete_arg(path);
            return filepath; 
        }
        free(filepath);
        i++;
    }
    ft_delete_arg(path);
    if (file)
        free(file);
    return (ft_strdup(file));
}