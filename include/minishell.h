/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 10:55:50 by akhastaf          #+#    #+#             */
/*   Updated: 2020/12/27 11:37:43 by akhastaf         ###   ########.fr       */
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
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <signal.h>

# define BUFFER_SIZE 1
# define ULIMIT 1
# define BUILTINS_NUM 7

# define IS_SCARACTER(x) (x == '$' || x == ';' x == '|')

typedef int fun_ptr(char **);
typedef struct s_red
{
    char *type;
    char *file;
    struct s_red *next;
}   t_red;


typedef struct  s_cmd
{
    char    *path; // /usr/bin/grep 
    char    **arg;  // ["grep", "hdjh", NULL]
    char    *opr; // "|" ";" NULL
    int     pipe[2];
    int     fdin;
    int     fdout;
    t_red   *red;
    struct s_cmd   *next;
    struct s_cmd   *prev;
}           t_cmd;

typedef struct s_sh
{
    t_cmd   *cmdlist;
    pid_t   pid;
    int     sigint;
    char    **env;
    fun_ptr *builtins_fun[BUILTINS_NUM];
    char    *builtins_str[BUILTINS_NUM];
    char    *line;
    int     status;
    int     in;
    int     out;
    int     is_b;
    int     ret;
    int     error;
    char    *errors[10];
    char    *home;
    int     c;
}       t_sh;
t_sh    g_sh;

// MINISHELLL
void        minishell_loop(char **env);
void    ft_print_prompt();
int    init_sh(char **env);
int    ft_envadd(char *var);
int        readline();
char    *ft_tilde(char *s, char *line, int i);
void    increment_shlvl();
void    ft_set_pwd();
void    ft_set_lstcmd();

// Parser
int get_next_line(int fd, char **line);
int		ft_readline(int fd, char **gard);
void    process_line();
char    *ft_refactor_line(char *s);
void    ft_warp_ref(t_cmd **cmd);

// Error
char    *check_syntax();
int     check_pipe();
int     check_red();
int     check_quote();

// ENV
char    *ft_getenv(char *var);
char    **ft_envcount(char *line);
char    *ft_envreplace(char *line);
char    *ft_getword(char *word, char *set);
int    ft_setenv(char *var, char *val);
int    ft_envremove(char *var);

//PATH
char *ft_getpath(char *file);

//EXECUTION
int     excute(t_cmd *cmdlist);
void     ft_launch(t_cmd *cmd);

// BUILTINS
int     builtins(t_cmd cmd);
int     builtins_pwd(char **arg);
int     builtins_env(char **arg);
int     builtins_cd(char **arg);
int     builtins_echo(char **arg);
int     builtins_unset(char **arg);
int     ft_isbuiltins(char *path);
void    builtins_init();

// REDIRECTION
t_red   *get_redirection(char *cmd);
char    *remove_red(char *cmd);
void    setup_redirection(t_cmd *cmd);
int    get_option(t_red *red);
void    close_fd(t_cmd *cmd);
int     ft_redcount(char *cmd, int l);

// PIPE
void    setup_pipe(t_cmd *cmd);
void    reset_std();
void    close_pipe();
void    open_pipes();

// UTILS
char		*ft_strjoin(char  *s1, char  *s2);
char		*ft_strdup(const char *s1);
char		*ft_strchr(const char *s, int c);
size_t      ft_strlen(char const *str);
char		*ft_strndup(const char *s1, size_t n);
char	*ft_checkerror(int fd, char **buff);
t_cmd	*ft_cmd_new(void *path, char **arg, char *opr, t_red *red);
void	ft_cmd_add_back(t_cmd **alst, t_cmd *new);
t_cmd	*ft_cmd_last(t_cmd *lst);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strtrim(char const *s1, char const *set);
char    *ft_strappend(char *str, char c);
char    *ft_strrepace(char *str);
int     ft_size_arg(char **arg);
char    **ft_argadd(char **arg, char *var);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void    print_arg(char **arg);
void    ft_cmd_remove(t_cmd *cmd);
void    ft_delete_arg(char **arg);
void    ft_cmd_list_remove(t_cmd **cmdlist);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int     ft_is_space(char c);
char			*ft_itoa(int n);
int     ft_strchrn(char *s, char c);
char    **ft_argtrim(char **arg, char *set);
char				**ft_split(char const *s, char *set);
char	*ft_strremove(char *s, char c);
int     ft_countcahr(char *s, char c);
void	ft_red_add_back(t_red **alst, t_red *new);
t_red	*ft_red_last(t_red *lst);
void    ft_red_list_remove(t_red **redlist);
t_red	*ft_red_new(void *type, char *file);
void    ft_red_remove(t_red *red);
int     ft_tab_min(int tab[], int i);
int     ft_strnchrn(char *s, char *set);
int		is_specialcar(char c);
int     ft_count_space(char *s);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
char     *ft_strnchr(char *s, char *set);
int     ft_is_empty(char *s);
void	*ft_memdel(void *ptr);
int		ft_tolower(int c);
char *ft_strtolower(char *str);
long		ft_atol(const char *str);
#endif