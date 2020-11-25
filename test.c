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
}           t_cmd;
int g_fd[2];
void    my_execute(t_cmd cmdlist);
void    set_pipe();

void    set_pipe()
{
    pipe(g_fd);
    dup2(g_fd[0], 0);
}
void    my_execute(t_cmd cmdlist)
{
    pid_t pid;

    if (cmdlist.opr)
        if (!strcmp(cmdlist.opr, "|"))
            set_pipe();
    pid = fork();
    waitpid(pid, NULL, 0);
    if (pid == 0)
    {
        execve(cmdlist.path, cmdlist.arg, NULL);
    }
}

int     main()
{
    t_cmd *cmdlist;
    pid_t pid;
    t_cmd *cmd;
    char *a[] = { "/sbin/ping", "-c", "2", "google.com", NULL };
    char *b[] = { "/bin/ls", "-all", NULL };
    
    cmdlist = malloc(sizeof(t_cmd));
    cmd = malloc(sizeof(t_cmd));

    cmdlist->path = "/sbin/ping";
    cmdlist->arg = a;
    cmdlist->opr = "|";
    cmdlist->next = cmd;

    cmd->path = "/bin/ls";
    cmd->arg = b;
    cmd->opr = NULL;
    cmd->next = NULL;



    while (cmdlist)
    {
        printf("%s\n", cmdlist->path);
        my_execute(*cmdlist);   
        cmdlist = cmdlist->next;
    }
}