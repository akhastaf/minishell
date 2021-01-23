#include "../../include/minishell.h"


char	*ft_strremove(char *s, char c)
{
	int l;
	int q;
	int i;
	char *new;

	l = 0;
	q = 0;
	l = ft_countcahr(s, c);
	if (!l)
		return ft_strdup(s);
	if (ft_strlen(s) ==  l)
		return ft_strdup("");
	if (!(new = malloc(sizeof(char) * (ft_strlen(s) - l + 1))))
		return NULL;
	l = 0;
	i = 0;
	while (s[l])
	{
		if (s[l] == '"' && !q)
			q = 1;
		else if (s[l] == '"' && q)
			q = 0;
		if ((s[l] != c) || (s[l] == c && q && c != '"') || (s[l + 1] == c))
		{
			new[i] = s[l];
			i++;
		}
		l++;
	}
	new[i] = 0;
	if (s)
	{
		free(s);
		s = NULL;
	}
	return new;
}