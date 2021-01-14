#include "../../include/minishell.h"

char     *ft_strnchr(char *s, char *set)
{
    size_t	i;
	size_t	j;

	if (set[0] == '\0')
		return (0);
	i = 0;
	j = 0;
	while (s[i + j])
	{
		if (s[i + j] == '"')
		{
			i++;
			while (s[i + j] && s[i + j] != '"')
				i++;
		}
		while (s[i + j] == set[j])
		{
			j++;
			if (set[j] == '\0')
				return (s + i);
            while (s[i+j] == ' ' || s[i + j] == '\t')
                i++;
		}
		j = 0;
		i++;
	}
    return NULL;
}