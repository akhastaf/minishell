#include "../../include/minishell.h"


char	*ft_strremove(char *s, char c)
{
	int l;
	int i;
	char *new;

	l = 0;
	l = ft_countcahr(s, c);
	if (!l)
		return ft_strdup(s);
	new = malloc(sizeof(char) * (ft_strlen(s) - l + 1));
	l = 0;
	i = 0;
	while (s[l])
	{
		if (s[l] != c)
		{
			new[i] = s[l];
			i++;
		}
		l++;
	}
	new[i] = 0;
	return new;
}