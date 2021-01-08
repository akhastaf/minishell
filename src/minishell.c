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
        printf("|%s|\n", arg[i]);
        i++;
    }
}

char    **ft_argadd(char **arg, char *var)
{
    int l;
    int i;
    char **new;
    
    l = ft_size_arg(arg);
    new = malloc(sizeof(char*) * (l + 2));
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
void    ft_printf_prompt()
{
    char *pwd;

    pwd = getcwd(NULL, 0);
    write(1, "\033[0;32m", 8);
    write(1, pwd, ft_strlen(pwd));
    write(1, "$> ", 3);
    write(1, "\033[0m", 5);
}
void        minishell_loop(char **env)
{
    int status;
    int r;
    char *tmp;

    status = 1;
    while(status)
    {
        g_sh.error = 0;
        g_sh.line = NULL;
        tmp = NULL;
        ft_printf_prompt();
        while ((r = readline()) == 0)
            tmp = ft_strjoin(tmp, g_sh.line);
        g_sh.line = ft_strjoin(tmp, g_sh.line);
        if (!check_syntax())
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
            ft_putendl_fd("syntax error", 2);
        free(g_sh.line);
        g_sh.pid = 0;
    }
}

void    init_sh(char **env)
{
    int l;
    int i;
    
    l = ft_size_arg(env);
    g_sh.env = malloc((l + 1) * sizeof(char*));
    i = 0;
    while (env[i])
    {
        g_sh.env[i] = ft_strdup(env[i]);
        i++;
    }
    g_sh.env[i] = NULL;
}

int    check_syntax()
{
    if (check_pipe())
        return 1;
    if (check_red())
        return 1;
    return 0;
}

int     check_pipe()
{
    int l;

    l = 0;
    while (g_sh.line[l] == ' ' || g_sh.line[l] == '\t')
        l++;
    if (g_sh.line[l] == '|' || g_sh.line[l] == ';')
        return 1;
    l = ft_strlen(g_sh.line);
    l--;
    while (g_sh.line[l])
    {
        if (g_sh.line[l] == ' ' || g_sh.line[l] == '\t')
            l--;
        if (g_sh.line[l] == '|')
            return 1;
        else
            break ;
    }
    return 0;
}

int     check_red()
{
    if (ft_strnchr(g_sh.line, "<<") || ft_strnchr(g_sh.line, ">>>"))
        return 1;
    return 0;
}

// int     check_