#include "../../include/minishell.h"

char		*ft_strndup(const char *s1, size_t n)
{
	char	*ptr;
	size_t	i;

	i = ft_strlen(s1);
	if (n > i)
		ptr = (char *)malloc((i + 1) * sizeof(char));
	else
		ptr = (char *)malloc((n + 1) * sizeof(char));
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