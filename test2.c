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
pid_t pid[2];
int    my_execute(t_cmd cmdlist, char **env);
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
    // close(1);
    close(g_fd[1]);
}
int    my_execute(t_cmd cmdlist, char **env)
{
    int status;
    pid_t pid;


   
    pid = fork();
    
    if (pid == 0 )
    {
        printf("%s\n", cmdlist.path);
        if (cmdlist.opr)
            if (!strcmp(cmdlist.opr, "|"))
                set_pipe_w();
        if (cmdlist.prev)
        {
            if (cmdlist.prev->opr)
            {
                if (!strcmp(cmdlist.prev->opr, "|"))
                    set_pipe_r();
            }
        }
        execve(cmdlist.path, cmdlist.arg, env);
    }
    else {
        //close(g_fd[0]);
        close(g_fd[1]);
        waitpid(pid, &status, 0);
    }
    return 1;
    
    // if (cmdlist.prev)
    // {
    //     if (!strcmp(cmdlist.prev->opr, "|"))
    //     {
    //         close(g_fd[0]);
    //         close(g_fd[1]);
    //     }
    // }
    
    
}

int     main(int ac, char **av, char **env)
{
    t_cmd *cmdlist;
    t_cmd *cmd;
    t_cmd *cmd1;
    char *str;
    char **t;
    char *a[] = { "ping", "-c", "2", "google.com", NULL };
    char *b[] = { "gerp", "round-trip min/avg/max/stddev", NULL };
    char *c[] = {"wc", NULL};
    
    cmdlist = malloc(sizeof(t_cmd));
    cmd = malloc(sizeof(t_cmd));
    cmd1 = malloc(sizeof(t_cmd));
    // ping -c 4 google.com | grep "statistics"
    // PATH
    // Builtins

    cmdlist->path = "/sbin/ping"; 
    cmdlist->arg = a;
    cmdlist->opr = "|";
    cmdlist->next = cmd;
    cmdlist->prev = NULL;

    cmd->path = "/usr/bin/grep";
    cmd->arg = b;
    cmd->opr = NULL;
    cmd->next = NULL;
    cmd->prev = cmdlist;

    cmd1->path = "/usr/bin/wc";
    cmd1->arg = c;
    cmd1->opr = NULL;
    cmd1->next = NULL;
    cmd1->prev = cmd;

    int status;

    str = strdup("ping -c 2 'google.com tes' | grep statistics ; cd ~");
    
    // int i = 0;
    // while (str[i])
    // {
    //     printf("%c %d\n", str[i], (int)str[i]);
    //     i++;
    // }
    // get_next_line(0, &str);
    // t = ft_split_two(str, '|', ';');
    // int i;
    // i = 0;
    // char **ping;
    // char *c;
    // c = ft_strrepace(t[0]);
    // printf("%s\n", c);
    // ping = ft_split(c, ',');
    
    // while (ping[i])
    // {
    //     printf("%s\n", ping[i]);
    //     i++;
    // }
    pipe(g_fd);
    while (cmdlist)
    {
        // if (execve(cmdlist->path, cmdlist->arg, env) < 0)
        //     printf("-bash: %s: command not found\n", cmdlist->path);
        my_execute(*cmdlist, env);
        cmdlist = cmdlist->next;
    }
}