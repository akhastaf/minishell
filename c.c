#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	char **av = malloc(sizeof(*av) * (4));

	av[0] = strdup("./minishell");
	av[1] = strdup("-c");
	av[2] = strdup("echo $PWD; echo $OLDPWD; cd .; pwd; echo $PWD; echo $OLDPWD");
	av[3] = NULL;

	char **envp = malloc(sizeof(*envp) * (3));
	envp[0] = strdup("PWD=lslslsls");
	envp[1] = strdup("PWDD=lslslsls");
	envp[2] = NULL;

	for (int i = 0; av[i]; i++)
		printf("av[%d] = |%s|\n", i, av[i]);
	for (int i = 0; envp[i]; i++)
		printf("envp[%d] = |%s|\n", i, envp[i]);

	execve(av[0], av, envp);
}
