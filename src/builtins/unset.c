/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 12:47:01 by akhastaf          #+#    #+#             */
/*   Updated: 2021/03/07 12:47:02 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtins_unset(char **arg)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	while (arg[i])
	{
		if (ft_strchr(arg[i], ' ') || ft_strchr(arg[i], '=')
			|| ft_is_empty(arg[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(arg[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			ret = 1;
		}
		ft_envremove(arg[i]);
		i++;
	}
	return (ret);
}
