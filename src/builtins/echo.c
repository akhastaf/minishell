/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 12:47:12 by akhastaf          #+#    #+#             */
/*   Updated: 2021/03/07 12:53:46 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtins_echo(char **arg)
{
	int		n;
	int		i;
	int		l;
	char	*p;

	n = check_dashn(arg, &i);
	while (arg[++i])
	{
		p = ft_strtrim(arg[i], " ");
		l = -1;
		while (p[++l])
		{
			while (p[l] && (p[l] == ' ' || p[l] == '\t'))
				l++;
			if (l - 1 >= 0 && (p[l - 1] == ' ' || p[l - 1] == '\t'))
				write(1, " ", 1);
			if (p[l])
				write(1, p + l, 1);
		}
		if (arg[i + 1])
			ft_putstr_fd(" ", 1);
		free(p);
	}
	if (!n)
		ft_putstr_fd("\n", 1);
	return (0);
}

int	check_dashn(char **arg, int *index)
{
	int	n;
	int	l;

	n = 0;
	*index = 1;
	while (arg[*index])
	{
		if (!ft_strcmp(arg[*index], "-n"))
			n = 1;
		else if (!ft_strncmp(arg[*index], "-n", 2))
		{
			l = 1;
			while (arg[*index][l] == 'n')
				l++;
			if (!arg[*index][l])
				n = 1;
			else
				break ;
		}
		else
			break ;
		(*index)++;
	}
	*index -= 1;
	return (n);
}
