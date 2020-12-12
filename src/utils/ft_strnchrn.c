#include "../../include/minishell.h"

int     ft_strnchrn(char *s, char *set)
{
    size_t	i;
	size_t	j;

	if (set[0] == '\0')
		return (0);
	i = 0;
	j = 0;
	while (s[i + j])
	{
		while (s[i + j] == set[j])
		{
			j++;
			if (set[j] == '\0')
				return (i);
		}
		j = 0;
		i++;
	}
    return 0;
}