#include "../include/minishell.h"

char    *ft_getenv(char *var)
{
    int i;
    int j;

    i = 0;
    while (g_sh.env[i])
    {
        j = 0;
        while (var[j])
        {
            if (g_sh.env[i][j] == 0 || var[j] != g_sh.env[i][j])
                break;
            j++;
        }
        if (j == ft_strlen(var))
                return g_sh.env[i] + j + 1;
        
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

char    **ft_envcount(char *line)
{
    int i;
    int j;
    char *w;
    char **evar;

    i = 0;
    j = 0;
    while (line[i])
    {
        if (line[i] == '$')
            j++;
        i++;
    }
    evar = malloc(sizeof(char*) * j + 1);
    j = 0;
    while (line[i])
    {
        if (line[i] == '$')
        {
            w = ft_getword(line + i + 1);
            evar[j] = ft_strdup(ft_getenv(w));
            printf("%s\n", evar[j]);
        }
        i++;
    }
    evar[j] = NULL;
    return evar;
}

char    *ft_envreplace(char *line)
{
    int i;
    int j;
    int k;
    char **evar;
    int len;
    char *new;

    evar = ft_envcount(line);
    printf("ft_envcount is working\n");
    i = 0;
    j = 0;
    len = 0;
    while (line[i])
    {
        if (line[i] == '$' && evar[j])
        {
            len += strlen(evar[j]) - 1;
            while (line[i] != ' ')
                i++;
            j++;
        }
        i++;
        len++;
    }
    printf("%d\n", len);
    new = malloc(len);
    i = 0;
    j = 0;
    k = 0;
    while (line[i])
    {
        if (line[i] == '$')
        {
            len = ft_strlen(evar[j]);
            ft_strlcpy(new + k, evar[j], len);
            k += len;
            while (line[i] != ' ')
                i++;
            j++;
        }
        new[k] = line[i];
        k++;
    }
    new[k] = 0;
    printf("%s\n", new);
    return new;

}
char    *ft_getword(char *word)
{
    int i;
    char *w;

    i = 0;
    while(word[i])
    {
        if (word[i] == ' ')
            break;
        i++;
    }
    w = ft_strndup(word, i);
    return (w);
}