/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 10:55:50 by akhastaf          #+#    #+#             */
/*   Updated: 2020/11/25 10:40:09 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

# define BUFFER_SIZE 1
# define ULIMIT 1

typedef struct  s_cmd
{
    char    *path;
    char    **arg;
    char    opr;
    struct s_cmd   *next;
}           t_cmd;
char    *g_line;

// MINISHELLL
void        minishell_loop(char **env);
void        readline();

// Parser
int get_next_line(int fd, char **line);
int		ft_readline(int fd, char **gard);
void    process_line();

// ENV
char    *ft_getenv(char **env, char *var);

// UTILS
char		*ft_strjoin(char  *s1, char  *s2);
char		*ft_strdup(const char *s1);
char		*ft_strchr(const char *s, int c);
size_t      ft_strlen(char const *str);
char		*ft_strndup(const char *s1, size_t n);
char	*ft_checkerror(int fd, char **buff);
char				**ft_split(char const *s, char c);
t_cmd	*ft_cmd_new(void *path, char **arg, char opr);
void	ft_cmd_add_back(t_cmd **alst, t_cmd *new);
t_cmd	*ft_lstlast(t_cmd *lst);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strtrim(char const *s1, char const *set);
char    *ft_strappend(char *str, char c);

#endif