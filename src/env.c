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

void    ft_setenv(char *var, char *val)
{
    int i;
    int j;
    char *new;

    new = malloc(sizeof(char) * (int)ft_strlen(val) + (int)ft_strlen(var) + 2);

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
                g_sh.env[i] = new;
        i++;
    }

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

void    ft_envadd(char *var)
{
    int l;
    int i;
    char **env;
    
    l = ft_size_arg(g_sh.env);
    env = malloc((l + 2 ) * sizeof(char*));
    ft_memcpy(env, g_sh.env, sizeof(char*) * l);
    env[l] = ft_strdup(var);
    env[l + 1] = NULL;
    g_sh.env = env;
    l = ft_size_arg(g_sh.env);
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