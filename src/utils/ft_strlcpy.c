#include "../../include/minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (size == 0)
		return (ft_strlen((char*)src));
	i = 0;
	while (i < size - 1 && src[i])
	{
		((char*)dst)[i] = ((char*)src)[i];
		i++;
	}
	((char*)dst)[i] = '\0';
	return (ft_strlen(((char*)src)));
}