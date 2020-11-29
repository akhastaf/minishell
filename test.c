#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "include/minishell.h"

// typedef struct  s_cmd
// {
//     char    *path;
//     char    **arg;
//     char    *opr;
//     struct s_cmd   *next;
//     struct s_cmd   *prev;
    
// }           t_cmd;
int g_fd[2];
void    my_execute(t_cmd cmdlist);
void    set_pipe_w();
void    set_pipe_r();

void    set_pipe_w()
{
    // pipe(g_fd);
    // printf("w r %d w %d\n", g_fd[0], g_fd[1]);
    dup2(g_fd[1], 1);
    close(g_fd[0]);
    close(g_fd[1]);
}
void    set_pipe_r()
{
    // pipe(g_fd);
    // printf("r r %d w %d\n", g_fd[0], g_fd[1]);
    dup2(g_fd[0], 0);
    close(g_fd[0]);
    close(g_fd[1]);
}
void    my_execute(t_cmd cmdlist)
{
    pid_t pid;
    int status;
    char str[1000];

    pipe(g_fd); // 16
    pid = fork();
    waitpid(pid, &status, 0);
    if (pid == 0)
    {
        if (cmdlist.opr)
            if (!strcmp(cmdlist.opr, "|"))
                set_pipe_w();
        if (cmdlist.prev)
        {
            printf("%s\n", str);
            if (cmdlist.prev->opr)
            {
                if (!strcmp(cmdlist.prev->opr, "|"))
                    set_pipe_r();
            }
        }
        execve(cmdlist.path, cmdlist.arg, NULL);
    }
}

int     main()
{
    t_cmd *cmdlist;
    pid_t pid;
    t_cmd *cmd;
    char *str;
    char **t;
    char *b[] = { "grep", "statistics", NULL };
    char *a[] = { "ping", "-c", "4", "google.com", NULL };
    
    cmdlist = malloc(sizeof(t_cmd));
    cmd = malloc(sizeof(t_cmd));
    // ping -c 4 google.com | grep "statistics"
    // PATH
    // Builtins

    cmdlist->path = "/sbin/ping"; 
    cmdlist->arg = a;
    cmdlist->opr = NULL;
    cmdlist->next = NULL;
    cmdlist->prev = NULL;

    cmd->path = "/usr/bin/grep";
    cmd->arg = b;
    cmd->opr = NULL;
    cmd->next = NULL;
    cmd->prev = cmdlist;

    str = strdup("ping -c 2 'google.com tes' | grep statistics ; cd ~");
    // int i = 0;
    // while (str[i])
    // {
    //     printf("%c %d\n", str[i], (int)str[i]);
    //     i++;
    // }
    get_next_line(0, &str);
    t = ft_split_two(str, '|', ';');
    int i;
    i = 0;
    char **ping;
    char *c;
    c = ft_strrepace(t[0]);
    printf("%s\n", c);
    ping = ft_split(c, ',');
    
    while (ping[i])
    {
        printf("%s\n", ping[i]);
        i++;
    }
    // while (cmdlist)
    // {
    //     my_execute(*cmdlist);
    //     //printf("%s\n", cmdlist->path);  
    //     cmdlist = cmdlist->next;
    // }
}