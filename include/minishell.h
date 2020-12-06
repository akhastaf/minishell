/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 10:55:50 by akhastaf          #+#    #+#             */
/*   Updated: 2020/12/06 13:46:43 by akhastaf         ###   ########.fr       */
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
#include <sys/types.h>
#include <sys/stat.h>

# define BUFFER_SIZE 1
# define ULIMIT 1
# define BUILTINS_NUM 5

typedef int fun_ptr(char **);

typedef struct  s_cmd
{
    char    *path; // /usr/bin/grep 
    char    **arg;
    char    *opr;
    char    *red;
    char    *file;
    struct s_cmd   *next;
    struct s_cmd   *prev;
}           t_cmd;

typedef struct s_sh
{
    t_cmd   *cmdlist;
    char    **env;
    fun_ptr *builtins_fun[BUILTINS_NUM];
    char    *builtins_str[BUILTINS_NUM];
    char    *line;
}       t_sh;
t_sh    g_sh;

// MINISHELLL
void        minishell_loop(char **env);
void    ft_printf_prompt();
void    init_sh(char **env);
void    ft_envadd(char *var);
void        readline();

// Parser
int get_next_line(int fd, char **line);
int		ft_readline(int fd, char **gard);
void    process_line();
void    ft_refactor_line();

// ENV
char    *ft_getenv(char *var);
char    **ft_envcount(char *line);
char    *ft_envreplace(char *line);
char    *ft_getword(char *word);
void    ft_setenv(char *var, char *val);
int    ft_envremove(char *var);

//PATH
char *ft_getpath(char *file);

// BUILTINS
int     builtins(t_cmd cmd);
int     builtins_pwd(char **arg);
int     builtins_env(char **arg);
int     builtins_cd(char **arg);
int     builtins_echo(char **arg);
int     builtins_unset(char **arg);
int     ft_isbuiltins(char *path);
void    builtins_init();


// UTILS
char		*ft_strjoin(char  *s1, char  *s2);
char		*ft_strdup(const char *s1);
char		*ft_strchr(const char *s, int c);
size_t      ft_strlen(char const *str);
char		*ft_strndup(const char *s1, size_t n);
char	*ft_checkerror(int fd, char **buff);
char				**ft_split(char const *s, char c);
t_cmd	*ft_cmd_new(void *path, char **arg, char *opr);
void	ft_cmd_add_back(t_cmd **alst, t_cmd *new);
t_cmd	*ft_lstlast(t_cmd *lst);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strtrim(char const *s1, char const *set);
char    *ft_strappend(char *str, char c);
char				**ft_split_two(char const *s, char c1, char c2);
char    *ft_strrepace(char *str);
int     ft_size_arg(char **arg);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void    print_arg(char **arg);
void    ft_cmd_remove(t_cmd *cmd);
void    ft_delete_arg(char **arg);
void    ft_cmd_list_remove(t_cmd **cmdlist);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int     ft_is_space(char c);

#endif