#include "../../include/minishell.h"

char		*ft_strjoin(char  *s1, char  *s2)
{
	size_t		i;
	char		*s;

	i = 0;
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!(s = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	i = 0;
	while (*s1)
	{
		*(s + i) = *s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		*(s + i) = *s2;
		i++;
		s2++;
	}
	*(s + i) = '\0';
	return (s);
}