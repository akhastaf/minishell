//#include "../include/minishell.h"

// void    set_pipe_w()
// {
//     // pipe(g_fd);
//     // printf("w r %d w %d\n", g_fd[0], g_fd[1]);
//     dup2(g_fd[1], 1);
//     close(g_fd[0]);
//     close(g_fd[1]);
// }
// void    set_pipe_r()
// {
//     // pipe(g_fd);
//     // printf("r r %d w %d\n", g_fd[0], g_fd[1]);
//     dup2(g_fd[0], 0);
//     close(g_fd[0]);
//     close(g_fd[1]);
// }