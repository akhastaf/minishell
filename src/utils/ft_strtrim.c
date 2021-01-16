#include "../../include/minishell.h"

// static size_t	ft_strstart(char *s, char *set)
// {
// 	size_t i;
// 	size_t j;

// 	i = 0;
// 	j = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == set[j] && s[(i - 1 < 0 ? 0 : i - 1)] != '\\' && set[j])
// 		{
// 			j = 0;
// 			i++;
// 		}
// 		else if (!set[j])
// 			break ;
// 		else
// 			j++;
// 	}
// 	return (i);
// }

// static size_t	ft_strend(char *s, char *set)
// {
// 	size_t i;
// 	size_t j;

// 	i = ft_strlen(s) - 1;
// 	j = 0;
// 	while (i)
// 	{
// 		if (s[i] == set[j] && s[(i - 1 < 0 ? 0 : i - 1)] != '\\' && set[j])
// 		{
// 			j = 0;
// 			i--;
// 		}
// 		else if (!set[j])
// 			break ;
// 		else
// 			j++;
// 	}
// 	return (i);
// }

// char			*ft_strtrim(char const *s1, char const *set)
// {
// 	char	*s;
// 	char	*c;
// 	char	*str;
// 	size_t	start;
// 	size_t	end;

// 	s = (char*)s1;
// 	c = (char*)set;
// 	if (!s1 || !set)
// 		return (NULL);
// 	start = ft_strstart(s, c);
// 	end = ft_strend(s, c);
// 	if (start == ft_strlen(s1))
// 	{
// 		if (!(str = malloc(1)))
// 			return NULL;
// 		str[0] = '\0';
// 		return (str);
// 	}
// 	str = ft_substr(s, start, (end - start + 1));
// 	return (str);
// }

static char	*ft_ctrim(char *s2, char *s3)
{
	char	*rtn;
	int		i;
	i = (unsigned long)s3 - (unsigned long)s2 + 1;
	rtn = (char*)malloc(sizeof(char) * (i + 1));
	if (rtn == NULL)
		return (NULL);
	i = 0;
	while (s2 != s3)
	{
		rtn[i] = *s2;
		i++;
		s2++;
	}
	rtn[i] = *s2;
	rtn[i + 1] = '\0';
	return (rtn);
}
static char	*f(void)
{
	char *s;
	s = (char*)malloc(sizeof(char) * 1);
	if (!s)
		return (NULL);
	*s = '\0';
	return (s);
}
char		*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	char	*s3;
	char	*s2;
	if (!s1 || !set)
		return (NULL);
	s2 = (char*)s1;
	s3 = (char*)s1 + ft_strlen(s1) - 1;
	i = -1;
	while (set[++i])
		if (*s2 == set[i])
		{
			s2++;
			i = -1;
		}
	i = -1;
	while (set[++i])
		if (*s3 == set[i])
		{
			s3--;
			i = -1;
		}
	return (!(*s2) ? f() : ft_ctrim(s2, s3));
}