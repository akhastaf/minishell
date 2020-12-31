#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "include/minishell.h"

int main()
{
    int fd;
    int fd1;
    fd = open("file", O_RDONLY);
    close(fd);
    fd1 = open("file", O_WRONLY);
    printf("fd %d fd1 %d\n", fd, fd1);
    // int fd[2];
    // pid_t pid;
    // pid_t pid1;
    // int s;
    // char *b[] = {"grep", "round-trip min/avg/max/stddev", NULL};
    // char *a[] = { "ping", "-c", "4", "google.com", NULL};

    // pipe(fd);
    // pid = fork();

    // if (pid == 0)
    // {
    //     dup2(fd[1], 1);
    //     close(fd[0]);
    //     close(fd[1]);

    //     execve("/sbin/ping", a, NULL);
    // }
    // pid1 = fork();
    // if (pid1 == 0)
    // {
    //     dup2(fd[0], 0);
    //     close(fd[0]);
    //     close(fd[1]);

    //     execve("/usr/bin/grep", b, NULL);
    // }
    // // close(fd[0]);
    // // close(fd[1]);
    // waitpid(pid, &s, 0);
    // waitpid(pid1, &s, 0);

    // printf("\nhello after pipe\n");

    return 0;
}