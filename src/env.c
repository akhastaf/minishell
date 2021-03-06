#include "../include/minishell.h"

int    ft_checkenv(char *var)
{
    char *tmp;

    tmp = ft_getenv(var);
    if (tmp)
    {
        free(tmp);
        return 1;
    }
    return (0);
}
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
                return ft_strdup(g_sh.env[i] + j + 1);
        
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
            free(g_sh.env[i]);
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
    int q;
    int sq;
    char *w;

    i = 0;
    q = 0;
    sq = 0;
    // printf("word : |%s|\n", word);
    while (word[i] == ' ')
        i++;
    while(word[i])
    {
        if (word[i] == '\'' && !sq && !q)
            sq = 1;
        else if (word[i] == '\'' && sq)
            sq = 0;
        if (word[i] == '"' && !q && !sq)
            q = 1;
        else if (word[i] == '"' && q)
            q = 0;
        if (ft_strchr(set, word[i]) && word[i] != ' ')
            break;
        else if (word[i] == ' ' && !q && !sq)
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
    env[l] = var;
    env[l + 1] = NULL;
    free(g_sh.env);
    g_sh.env = env;
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