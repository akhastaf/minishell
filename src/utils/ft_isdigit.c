int		ft_isdigit(int c)
{
	if ((c >= 48 && c <= 57) || c == '+' || c == '-')
		return (1);
	return (0);
}