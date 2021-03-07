#include "../../include/minishell.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		signe;
	size_t	n;

	i = 0;
	signe = 1;
	n = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			signe = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57 && str[i] != '\0')
	{
		n = n * 10 + str[i] - 48;
		if (n > 9223372036854775807)
		{
			if (signe > 0)
				return (1);
			return (0);
		}
		i++;
	}
	return ((int)(n * signe));
}
