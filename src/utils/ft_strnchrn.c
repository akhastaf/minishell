#include "../../include/minishell.h"

int     ft_strnchrn(char *s, char *set)
{
	int i;
	int j;

	if (set[0] == '\0')
		return (0);
	i = 0;
	while (s[i])
	{
		j = 0;
		while (set[j])
		{
			if (s[i] == set[j])
				return i;
			j++;
		}
		i++;
	}
	return 0;
}