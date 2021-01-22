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
        if (g_sh.env[i][j] == '=' && ft_strlen(var) == j)
                return g_sh.env[i] + j + 1;
        
        i++;
    }
    return (NULL);
}

int    ft_setenv(char *var, char *val)
{
    int i;
    int j;
    char *new;

    if (!(new = malloc(sizeof(char) * (int)ft_strlen(val) + (int)ft_strlen(var) + 2)))
        return 0;
    i = 0;
    while (var[i])
    {
        new[i] = var[i];
        i++;
    }
    new[i] = '=';
    i++;
    j = 0;
    while (val[j])
    {
        new[i] = val[j];
        i++;
        j++;
    }
    new[i] = 0;
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
        {
            g_sh.env[i] = new;
            return 1;
        }
        i++;
    }
    if (j != ft_strlen(var))
        ft_envadd(new);
    return 0;

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
    if (!(evar = malloc(sizeof(char*) * j + 1)))
        return NULL;
    j = 0;
    while (line[i])
    {
        if (line[i] == '$')
        {
            w = ft_getword(line + i + 1, " ");
            evar[j] = ft_strdup(ft_getenv(w));
            printf("%s\n", evar[j]);
        }
        i++;
    }
    evar[j] = NULL;
    return evar;
}

char    *ft_getword(char *word, char *set)
{
    int i;
    char *w;

    i = 0;
    while (word[i] == ' ')
        i++;
    while(word[i])
    {
        if (ft_strchr(set, word[i]))
            break;
        i++;
    }
    w = ft_strndup(word, i);
    return (w);
}

int    ft_envadd(char *var)
{
    int l;
    int i;
    char **env;
    
    l = ft_size_arg(g_sh.env);
    if (!(env = malloc((l + 2 ) * sizeof(char*))))
        return 0;
    ft_memcpy(env, g_sh.env, sizeof(char*) * l);
    env[l] = ft_strdup(var);
    env[l + 1] = NULL;
    g_sh.env = env;
    l = ft_size_arg(g_sh.env);
    return 1;
}

int    ft_envremove(char *var)
{
    int i;
    int j;
    int l;

    i = 0;
    l = ft_strlen(var);
    while (g_sh.env[i])
    {
        if (!ft_strncmp(g_sh.env[i], var, l) && g_sh.env[i][l] == '=')
        {
            j = 0;
            free(g_sh.env[i]);
            while (g_sh.env[i + j])
            {
                g_sh.env[i + j] = g_sh.env[i + j + 1];
                j++;
            }
            return 1;
        }
        i++;
    }
    return 0;
}