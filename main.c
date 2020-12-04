/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 10:55:52 by akhastaf          #+#    #+#             */
/*   Updated: 2020/12/03 19:03:12 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"
#include <fcntl.h>
#include<sys/wait.h>

int     main(int ac, char **av, char **env)
{
    init_sh(env);
    // ft_envadd("AH=bi");
    // printf("%s\n", ft_getenv("AH"));
    //print_arg(g_sh.env);
    //print_arg(g_sh.env);
    minishell_loop(env);
    return 0;
}