#include "../include/minishell.h"

char    *ft_getopr(char *cmd)
{
    int len;

    len = ft_strlen(cmd);
    if (cmd[len-1] == '|' && cmd[len-2] != '\\')
        return (ft_strdup("|"));
    else if (cmd[len-1] == ';'  && cmd[len-2] != '\\')
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
    if (ft_strchr(arg[(i - 1 < 0 ? 1 : i - 1)], '|') || ft_strchr(arg[(i - 1 < 0 ? 1 : i - 1)], ';'))
    {
        l = ft_strlen(arg[(i - 1 < 0 ? 1 : i - 1)]);
        arg[(i - 1 < 0 ? 1 : i - 1)][l - 1] = 0;
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
            arg =  ft_split(cmd[i], " \t");
            if (opr)
                arg = ft_remove_arg(arg, opr);
            if (!arg[0])
                arg[0] = ft_strdup("");    
            new = ft_cmd_new(ft_strtrim(ft_getpath(ft_strtrim(arg[0], " ")), " "), arg, opr, red);
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
    int j;

    line = NULL;
    i = 0;
    while (s[i])
    {
        if (s[i] == '\'' && s[(i - 1 < 0 ? 1 : i - 1)] != '\\')
        {
            i++;
            while (s[i] != '\'')
            {
                line = ft_strappend(line, s[i]);
                i++;
            }
        }
        if (s[i] == '$' && !ft_is_space(s[i + 1]) && s[(i - 1 < 0 ? 1 : i - 1)] != '\\')
        {
            var = ft_getword(s + i + 1, "\" '\\$=");
            if (s[i + 1] == '?')
            {
                line = ft_strjoin(line, ft_itoa(g_sh.status));
                i++;
            }
            else if (var[0])
            {
                line = ft_strjoin(line, ft_getenv(var));
                i = i + ft_strlen(var);
            }
            else
                line = ft_strappend(line, s[i]);
        }
        else if (s[i] == '~'  && s[(i - 1 < 0 ? 1 : i - 1)] != '\\')
        {
            line = ft_tilde(s, line, i);
            i = (s[i + 1] == '+' ? i + 1 : i) + (s[i + 1] == '-' ? i + 1 : i);
        }
        else
            line = ft_strappend(line, s[i]);
        i++;
    }
    free(s);
    return line;
}

char    *ft_tilde(char *s, char *line, int i)
{
    if (s[i + 1] == '+' && ft_getenv("PWD") && (ft_is_space(s[i+ 2]) || s[i+2]==0))
        return ft_strjoin(line, ft_getenv("PWD"));
    else if (s[i + 1] == '-' && ft_getenv("OLDPWD")  && (ft_is_space(s[i+ 2]) || s[i+2]==0))
        return ft_strjoin(line, ft_getenv("OLDPWD"));
    else if (s[i + 1] == '+' || s[i + 1] == '-')
    {
            line = ft_strappend(line, '~');
            line = ft_strappend(line, s[i+1]);
    }
    else
    {
        if (ft_getenv("HOME"))
            return ft_strjoin(line, ft_getenv("HOME"));
        else
        {
            printf("%s\n", g_sh.home);
            return ft_strjoin(line, g_sh.home);
        }
    }
    return line;
}