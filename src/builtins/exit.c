/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 12:41:31 by akhastaf          #+#    #+#             */
/*   Updated: 2021/03/07 14:41:01 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exit_skip(char *s, int *i)
{
	while (s[*i] && (s[*i] == ' ' || s[*i] == '\t'
			|| s[*i] == '\r' || s[*i] == '\f'))
		(*i)++;
}

int	builtins_exit(char **arg)
{
	int	i;

	i = 0;
	if (arg[1])
	{
		ft_exit_skip(arg[1], &i);
		if (ft_strisdigit(ft_strtrim(arg[1] + i, " \t")))
			g_sh.ret = ft_atoll(arg[1] + i);
		else if (g_sh.ret > 9223372036854775807 || !ft_strisdigit(arg[1]))
		{
			ft_puterror("exit\nminishell: exit: ", arg[1],
					": numeric argument required");
			exit(255);
		}
		if (ft_size_arg(arg) > 2)
		{
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			return (1);
		}
		g_sh.ret = g_sh.ret % 256;
		ft_putendl_fd("exit", 2);
		exit(g_sh.ret);
	}
	ft_putendl_fd("exit", 2);
	exit(g_sh.status);
	return (g_sh.ret);
}
