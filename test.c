#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct  s_cmd
{
    char    *path;
    char    **arg;
    char    *opr;
    struct s_cmd   *next;
    struct s_cmd   *prev;
    
}           t_cmd;
int g_fd[2];
void    my_execute(t_cmd cmdlist);
void    set_pipe_w();
void    set_pipe_r();

void    set_pipe_w()
{
    pipe(g_fd);
    dup2(g_fd[1], 1);
    close(g_fd[0]);
    close(g_fd[1]);
}
void    set_pipe_r()
{
    pipe(g_fd);
    dup2(g_fd[0], 0);
    close(g_fd[0]);
    close(g_fd[1]);
}
void    my_execute(t_cmd cmdlist)
{
    pid_t pid;

    
    pid = fork();
    waitpid(pid, NULL, 0);
    if (pid == 0)
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
        execve(cmdlist.path, cmdlist.arg, NULL);
    }
}

int     main()
{
    t_cmd *cmdlist;
    pid_t pid;
    t_cmd *cmd;
    char *b[] = { "/usr/bin/grep", "statistics", NULL };
    char *a[] = { "/sbin/ping", "-c", "4", "google.com", NULL };
    
    cmdlist = malloc(sizeof(t_cmd));
    cmd = malloc(sizeof(t_cmd));

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

    while (cmdlist)
    {
        my_execute(*cmdlist);
        //printf("%s\n", cmdlist->path);  
        cmdlist = cmdlist->next;
    }
}