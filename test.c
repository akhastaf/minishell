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
int std[2];
int    my_execute(t_cmd cmdlist, char **env);
void    set_pipe_w();
void    set_pipe_r();

void    set_pipe_w()
{
    // pipe(g_fd);
    // printf("w r %d w %d\n", g_fd[0], g_fd[1]);
    dup2(g_fd[1], 1);
    // close(g_fd[0]);
    close(g_fd[1]);
}
void    set_pipe_r()
{
    // pipe(g_fd);
    // printf("r r %d w %d\n", g_fd[0], g_fd[1]);
    dup2(g_fd[0], 0);
    // close(g_fd[0]);
    close(g_fd[1]);
}
int    my_execute(t_cmd cmdlist, char **env)
{
    int status;
    pid_t pid;

    int k = dup(1);
    pipe(g_fd);
       printf("cmd : %s\nopr : %s\n", cmdlist.path, cmdlist.opr);
       if (cmdlist.opr)
       {
            if (!strcmp(cmdlist.opr, "|"))
            {
                // close(g_fd[0]);
                write(g_fd[1], "test", 4);
                close(g_fd[1]);
                //set_pipe_w();
            }

       }
        if (cmdlist.prev && cmdlist.prev->opr)
        {
            if (!strcmp(cmdlist.prev->opr, "|"))
            {
                //set_pipe_r();
                char buff[100];
                bzero(buff, 100);
                dup2(k, 1);
                // close(g_fd[0]);
                read(g_fd[0], buff, 100);
                printf("%s\n", buff);
                write(1, "write", 5);
            }
                
        }
//     pid = fork();
//     //close(g_fd[0]);
//     //close(g_fd[1]);

//    if (pid == 0)
//    {
//         write (1, "for test\n", 9);
//         exit(0);
//         // execve(cmdlist.path, cmdlist.arg, env);
//     }
//     if (pid)
//     {
//         // close(g_fd[0]);
//         waitpid(pid, &status, 0);
        
//         status = WEXITSTATUS(status);
//         printf("%d\n",status);
//     }
    return 1;
}

int     main(int ac, char **av, char **env)
{
    t_cmd *cmdlist;
    t_cmd *cmd;
    t_cmd *cmd1;
    char *str;
    char **t;
    char *a[] = { "ping", "-c", "4", "google.com", NULL };
    char *b[] = { "gerp", "round-trip min/avg/max/stddev", NULL };
    char *c[] = {"wc", NULL};
    
    cmdlist = malloc(sizeof(t_cmd));
    cmd = malloc(sizeof(t_cmd));
    cmd1 = malloc(sizeof(t_cmd));
    std[0] = dup(0);
    std[1] = dup(1);
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
    while (cmdlist)
    {
        // if (execve(cmdlist->path, cmdlist->arg, env) < 0)
        //     printf("-bash: %s: command not found\n", cmdlist->path);
        my_execute(*cmdlist, env);
        //dup2(std[0], 0);
        // dup2(std[1], 1);
        cmdlist = cmdlist->next;
    }
    // close(g_fd[0]);
    // close(g_fd[1]);
    // waitpid(pid[0], &status, 0);
    // waitpid(pid[1], &status, 0);
}