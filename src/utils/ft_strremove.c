#include "../../include/minishell.h"


char	*ft_strremove(char *s, char c)
{
	int l;
	int q;
	int sq;
	int i;
	char *new;

	l = 0;
	q = 0;
	sq = 0;

	if (!(new = malloc(sizeof(char) * (ft_strlen(s)  + 1))))
		return NULL;
	l = 0;
	i = 0;
	while (s[l])
	{
		if (s[l] == '"' && !q && !sq)
			q = 1;
		else if (s[l] == '"' && q)
			q = 0;
		if (s[l] == '\'' && !sq && !q)
			sq = 1;
		else if (s[l] == '\'' && sq)
			sq = 0;
		if (c == '"' && s[l] == c && ((s[l - 1 > 0 ? l - 1 : 0] == '\\' && count_backslash(ft_strndup(s, l)) % 2 != 0) || sq)) 
		{
			new[i] = s[l];
			i++;
		}
		if ((c == '\'' && s[l] == c) && q)
		{
			new[i] = s[l];
			i++;
		}
		if (c == '\\' && s[l] == c && (sq || (s[l - 1 > 0 ? l - 1 : 0] == '\\' && count_backslash(ft_strndup(s, l)) % 2 != 0)))
		{
			new[i] = s[l];
			i++;
		}
		if ((s[l] != '\\' && c == '\\') || (s[l] != '"' && c == '"') || (s[l] != '\'' && c == '\''))
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