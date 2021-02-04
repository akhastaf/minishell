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

	l = ft_countcahr(s, c);
	if (!l)
		return ft_strdup(s);
	if (ft_strlen(s) ==  l)
		return ft_strdup("");
	if (!(new = malloc(sizeof(char) * (ft_strlen(s) - l + 2))))
		return NULL;
	l = 0;
	i = 0;
	// printf("|%s|\n", s);
	while (s[l])
	{
		if (s[l] == '"' && !q && !sq)
			q = 1;
		else if (s[l] == '"' && q)
			q = 0;
		if (s[l] == '\'' && !sq)
			sq = 1;
		else if (s[l] == '\'' && sq)
			sq = 0;
		if ((s[l] != c) || (s[l] == c && q && c != '"') || (c == '\\' && (s[l + 1] == c)))
		{
			new[i] = s[l];
			i++;
		}
		else if ((s[l - 1 > 0 ? l - 1 : 0] == '\\' && is_specialcar(s[l]) && c != '\''))
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