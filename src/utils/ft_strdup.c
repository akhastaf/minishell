#include "../../include/minishell.h"

char		*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	i;

	i = 0;
	while (*(s1 + i))
		i++;
	if (!(ptr = (char *)malloc((i + 1) * sizeof(char))))
		return NULL;
	if (!ptr)
		return (NULL);
	i = 0;
	while (*(s1 + i))
	{
		*(ptr + i) = *(s1 + i);
		i++;
	}
	*(ptr + i) = '\0';
	return (ptr);
}