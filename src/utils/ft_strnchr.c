#include "../../include/minishell.h"

char     *ft_strnchr(char *s, char *set)
{
    size_t	i;
	size_t	j;
	int q;
	int sq;
	int len;

	if (set[0] == '\0')
		return (0);
	i = 0;
	j = 0;
	len = ft_strlen(s);
	q = 0;
	sq = 0;
	while (s[i + j])
	{
		if (s[i + j] == '"' && !q && !sq)
			q = 1;
		else if (s[i + j] == '"' && q)
			q = 0;
		if (s[i + j] == '\'' && !sq && !q)
			sq = 1;
		else if (s[i + j] == '\'' && sq)
			sq = 0;
		while (s[i + j] && s[i + j] == set[j])
		{
			j++;
			if (set[j] == '\0' && !sq && !q)
				return (s + i);
            while (s[i+j] == ' ' || s[i + j] == '\t')
                i++;
		}
		j = 0;
		i++;
	}
    return NULL;
}