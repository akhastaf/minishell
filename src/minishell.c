/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 10:55:46 by akhastaf          #+#    #+#             */
/*   Updated: 2020/12/27 11:38:21 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void    print_arg(char **arg)
{
    int i;
    
    i = 0;
    while (arg[i])
    {
        printf("arg[%d] = |%s|\n", i, arg[i]);
        i++;
    }
}

char    **ft_argadd(char **arg, char *var)
{
    int l;
    int i;
    char **new;
    
    l = ft_size_arg(arg);
    if (!(new = malloc(sizeof(char*) * (l + 2))))
        return NULL;
    ft_memcpy(new, arg, sizeof(char *) * l);
    new[l] = ft_strdup(var);
    new[l+1] = NULL;
    return new;
}

void    print_red(t_red *red)
{
    while (red)
    {
        printf("type : %s | file : %s\n", red->type, red->file);
        red = red->next;
    }
}

void	print_cmd(t_cmd *l)
{
	t_cmd *tmp = l;
	if (!tmp)
		printf("NULL\n");
	while (tmp)
	{
		printf("path |%s|\n", tmp->path);
        print_arg(tmp->arg);
        print_red(tmp->red);
        printf("opr |%s|\n", tmp->opr);
		tmp = tmp->next;
	}
}
void    ft_print_prompt()
{
    char *pwd;

    if (!(pwd = getcwd(NULL, 0)))
        pwd = ft_getenv("PWD");
    ft_putstr_fd("\033[0;32m", 2);
    if (pwd)
        ft_putstr_fd(pwd, 2);
    ft_putstr_fd("$>\033[0m", 2);
}
void        minishell_loop()
{
    int status;
    int r;
    char *tmp;
    char *err;

    status = 1;
    while(status)
    {
        g_sh.error = 0;
        if (!g_sh.c)
        {
            g_sh.line = NULL;
            tmp = NULL;
            ft_print_prompt();
            while ((r = readline()) <= 0)
                tmp = ft_strjoin(tmp, g_sh.line);
            g_sh.line = ft_strjoin(tmp, g_sh.line);
        }
        if (!(err = check_syntax()))
        {
            process_line();
            open_pipes();
            // print_cmd(g_sh.cmdlist);
            g_sh.status = excute(g_sh.cmdlist);
            close_pipe();
            ft_cmd_list_remove(&g_sh.cmdlist);
            reset_std();
            g_sh.cmdlist = NULL;
        }else
        {
            ft_putendl_fd(err, 2);
            g_sh.status = 258;
        }
        free(g_sh.line);
        if (g_sh.c)
            exit(g_sh.status);
        g_sh.pid = 0;
    }
}

int    init_sh(char **env)
{
    int l;
    int i;
    
    l = ft_size_arg(env);
    if (!(g_sh.env = malloc((l + 1) * sizeof(char*))))
        return 0;
    i = 0;
    while (env[i])
    {
        g_sh.env[i] = ft_strdup(env[i]);
        i++;
    }
    g_sh.env[i] = NULL;
    return 1;
}

char    *check_syntax()
{
    int r;
    g_sh.errors[1] = ft_strdup("minishell: syntax error near unexpected token `|'");
    g_sh.errors[2] = ft_strdup("minishell: syntax error near unexpected token `;'");
    g_sh.errors[3] = ft_strdup("minishell: syntax error near unexpected token `||'");
    g_sh.errors[4] = ft_strdup("minishell: syntax error near unexpected token `;;'");
    g_sh.errors[5] = ft_strdup("minishell: syntax error near unexpected token `|;'");
    g_sh.errors[6] = ft_strdup("minishell: syntax error near unexpected token `;|'");
    g_sh.errors[7] = ft_strdup("minishell: syntax error near unexpected token `<<'");
    g_sh.errors[8] = ft_strdup("minishell: syntax error near unexpected token `>'");
    g_sh.errors[9] = ft_strdup("minishell: syntax error near unexpected token `newline'");
    g_sh.errors[10] = ft_strdup("minishell: syntax error multiline");

    if ((r = check_pipe()))
        return g_sh.errors[r];
    if ((r = check_red()))
        return g_sh.errors[r];
    if ((r = check_quote()))
        return g_sh.errors[r];
    return NULL;
}

int     check_pipe()
{
    int l;

    l = 0;
    while (g_sh.line[l] == ' ')
        l++;
    if (g_sh.line[l] == '|')
        return 1;
    else if (g_sh.line[l] == ';')
        return 2;
    l = ft_strlen(g_sh.line);
    l--;
    while (g_sh.line[l])
    {
        if (g_sh.line[l] == ' ')
            l--;
        if (g_sh.line[l] == '|')
            return 1;
        else
            break ;
    }
    if (ft_strnchr(g_sh.line, "||"))
        return 3;
    if (ft_strnchr(g_sh.line, ";;"))
        return 4; 
    if (ft_strnchr(g_sh.line, "|;"))
        return 5;
    if (ft_strnchr(g_sh.line, ";|"))
        return 6;
    return 0;
}

int     check_red()
{
    int i;

    if (ft_strnchr(g_sh.line, "<<"))
        return 7;
    if (ft_strnchr(g_sh.line, ">>>"))
        return 8;
    i = 0;
    while (g_sh.line[i])
    {
        if (g_sh.line[i] == '>' && g_sh.line[i + 1] == '>')
        {
            i+= 2;
            while (g_sh.line[i] == ' ')
                i++;
            if (g_sh.line[i] != '$' && (is_specialcar(g_sh.line[i]) || !g_sh.line[i]))
                return 9;
        }
        else if (g_sh.line[i] == '>' || g_sh.line[i] == '<')
        {
            i++;
            while (g_sh.line[i] == ' ')
                    i++;
            if (g_sh.line[i] != '$' && (is_specialcar(g_sh.line[i]) || !g_sh.line[i]))
                return 9;
        }
        i++;
    }
    return 0;
}

int     check_quote()
{
    if (count_doubleq(g_sh.line) % 2 != 0)
        return 10;
    if (count_singleq(g_sh.line) % 2 != 0)
        return 10;
    return 0;
}

int     count_singleq(char *str)
{
    int i;
    int j;
    int q;
    int sq;

    i = 0;
    q = 0;
    sq = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] == '"' && !q && !sq)
            q = 1;
        else if (str[i] == '"' && q)
            q = 0;
        if (str[i] == '\'' && !sq && !q)
            sq = 1;
        else if (str[i] == '\'' && sq)
            sq = 0;
        if (str[i] == '\'' && !q)
            j++;
        i++;
    }
    return j;
}

int     count_doubleq(char *str)
{
    int i;
    int j;
    int sq;
    int q;

    i = 0;
    sq = 0;
    q = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] == '\'' && !sq && !q)
            sq = 1;
        else if (str[i] == '\'' && sq)
            sq = 0;
        if (str[i] == '"' && !q)
            q = 1;
        else if (str[i] == '"' && q)
            q = 0;
        if (str[i] == '"' && !sq && str[(i - 1 < 0 ? 0 : i - 1)] != '\\')
            j++;
        i++;
    }
    return j;
}