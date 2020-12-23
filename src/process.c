#include "../include/minishell.h"

char    *ft_getopr(char *cmd)
{
    int len;

    len = ft_strlen(cmd);
    if (cmd[len-1] == '|')
        return (ft_strdup("|"));
    else if (cmd[len-1] == ';')
        return (ft_strdup(";"));
    return NULL;
}

char    **ft_remove_arg(char **arg, char *str)
{
    int i;
    int l;

    i = 0;
    while (arg[i])
    {
        if (!ft_strcmp(arg[i], str))
        {
            free(arg[i]);
            arg[i] = NULL;
            return arg;
        }
        i++;
    }
    if (ft_strchr(arg[i - 1], '|') || ft_strchr(arg[i - 1], ';'))
    {
        l = ft_strlen(arg[i - 1]);
        arg[i - 1][l - 1] = 0;
    }
    return arg;
}

void    process_line()
{
    char **arg;
    char **cmd;
    char *opr;
    t_cmd *new;
    t_red *red;
    int i;

    if (g_sh.line)
    {
        new = NULL;
        cmd = ft_split(g_sh.line, "|;");
        cmd = ft_argtrim(cmd, " ");
        i = 0;
        while (cmd[i])
        {
            red = get_redirection(cmd[i]);
            opr = ft_getopr(cmd[i]);
            cmd[i] = remove_red(cmd[i]);
            arg =  ft_split(cmd[i], " ");
            if (opr)
                arg = ft_remove_arg(arg, opr);
            arg = ft_argtrim(arg, "'\"");
            new = ft_cmd_new(ft_strtrim(ft_getpath(arg[0]), " "), arg, opr, red);
            ft_cmd_add_back(&g_sh.cmdlist, new);
            if (!opr && cmd[i + 1])
                break;
            i++;
        }
    }
}

char    *ft_refactor_line(char *s)
{
    char *var;
    char *line;
    int i;

    line = NULL;
    i = 0;
    while (s[i])
    {
        if (s[i] == '$' && !ft_is_space(s[i + 1]) && s[i - 1] != '\\')
        {
            if (s[i + 1] == '?')
            {
                line = ft_strjoin(line, ft_itoa(g_sh.status));
                i++;
            }
            else
            {
                var = ft_getword(s + i + 1, " ");
                line = ft_strjoin(line, ft_getenv(var));
                i = i + ft_strlen(var);
            }
        }
        else if (s[i] == '~'  && s[i - 1] != '\\')
        {
            line = ft_tilde(line, i);
            i = (s[i + 1] == '+' ? i + 1 : i);
        }
        else
            line = ft_strappend(line, s[i]);
        i++;
    }
    free(s);
    return line;
}

char    *ft_tilde(char *line, int i)
{
    if (g_sh.line[i + 1] == '+')
        return ft_strjoin(line, ft_getenv("PWD"));
    else
        return ft_strjoin(line, ft_getenv("HOME"));
}