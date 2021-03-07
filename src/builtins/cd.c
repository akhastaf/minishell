/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 12:47:09 by akhastaf          #+#    #+#             */
/*   Updated: 2021/03/07 12:47:10 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int     builtins_cd(char **arg)
{
    char *oldpwd;
    char *pwd;
    char *str;
    char *tmp;

    str = ft_strdup(arg[1]);
    oldpwd = ft_checkenv("PWD") ? ft_getenv("PWD") : ft_strdup("");
    if (!arg[1])
    {
        if (!(str = ft_getenv("HOME")))
        {
            ft_putendl_fd("minishell: cd: HOME not set", 2);
            return 1;
        }
    }
    else if (str[0] == '\0' && oldpwd)
    {
        ft_setenv("OLDPWD", oldpwd);
        return 1;
    }
    if (!ft_strcmp(str, "-"))
    {
        free(str);
        str = ft_getenv("OLDPWD");
        if (str)
            ft_putendl_fd(str, 1);
        else
        {
            ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
            return 1;
        }
    }
    if (!chdir(str))
    {
        if (!(pwd = getcwd(NULL, 0)))
        {
            ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: ", 2);
            ft_putendl_fd(strerror(errno), 2);
            pwd = ft_getenv("PWD");
            pwd = ft_strappend(pwd, '/');
            tmp = pwd;
            pwd = ft_strjoin(pwd, str);
            free(tmp);
        }
        ft_setenv("PWD", pwd);
        if (oldpwd)
            ft_setenv("OLDPWD", oldpwd);
        free(pwd);
        free(oldpwd);
    }
    else
    {
        ft_putstr_fd("minishell: cd: ", 2);
        ft_putstr_fd(str, 2);
        ft_putstr_fd(": ", 2);
        ft_putendl_fd(strerror(errno), 2);
        if (!arg[1])
            free(str);
        return 1;
    }
    free(str);
    return 0;
}

char        *get_oldpwd()
{
    char *oldpwd;
    oldpwd = ft_getenv("OLDPWD");
    if (!oldpwd)
        ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
    return oldpwd;
}