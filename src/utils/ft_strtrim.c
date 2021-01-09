#include "../../include/minishell.h"

static size_t	ft_strstart(char *s, char *set)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == set[j] && s[i - 1] != '\\' && set[j])
		{
			j = 0;
			i++;
		}
		else if (!set[j])
			break ;
		else
			j++;
	}
	return (i);
}

static size_t	ft_strend(char *s, char *set)
{
	size_t i;
	size_t j;

	i = ft_strlen(s) - 1;
	j = 0;
	while (i)
	{
		if (s[i] == set[j] && s[i - 1] != '\\' && set[j])
		{
			j = 0;
			i--;
		}
		else if (!set[j])
			break ;
		else
			j++;
	}
	return (i);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*s;
	char	*c;
	char	*str;
	size_t	start;
	size_t	end;

	s = (char*)s1;
	c = (char*)set;
	if (!s1 || !set)
		return (NULL);
	start = ft_strstart(s, c);
	end = ft_strend(s, c);
	if (start == ft_strlen(s1))
	{
		if (!(str = malloc(1)))
			return NULL;
		str[0] = '\0';
		return (str);
	}
	str = ft_substr(s, start, (end - start + 1));
	return (str);
}