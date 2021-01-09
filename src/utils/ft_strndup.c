#include "../../include/minishell.h"

char		*ft_strndup(const char *s1, size_t n)
{
	char	*ptr;
	size_t	i;

	i = ft_strlen(s1);
	if (n > i)
	{
		if (!(ptr = (char *)malloc((i + 1) * sizeof(char))))
			return NULL;
	}
	else
	{
		if (!(ptr = (char *)malloc((n + 1) * sizeof(char))))
			return NULL;
	}
	if (!ptr)
		return (NULL);
	i = 0;
	while (*(s1 + i) && n--)
	{
		*(ptr + i) = *(s1 + i);
		i++;
	}
	*(ptr + i) = '\0';
	return (ptr);
}