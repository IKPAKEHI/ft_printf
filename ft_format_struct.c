
#include "ft_printf.h"



int		iis(char c)
{
	if (c == ' ' || c == '#' || c == '-' || c == '+')
		return (1);
	else
		return (0);
}

void	init_format(t_flags **formatt)
{
	int i;

	(*formatt) = (t_flags*)malloc(sizeof(t_flags));
	i = -1;
	while (++i < 5)
		(*formatt)->flags[i] = 0;
	(*formatt)->width_star = 0;
	(*formatt)->width_len = 0;
	(*formatt)->precision_star = 0;
	(*formatt)->precision_len = 0;
	(*formatt)->type = 0;
}

void	check_flags(char c, t_flags **formatt)
{
	if (c == '-')
		(*formatt)->flags[0] = 1;
	if (c == '+')
		(*formatt)->flags[1] = 1;
	if (c == ' ')
		(*formatt)->flags[2] = 1;
	if (c == '#')
		(*formatt)->flags[3] = 1;
	if (c == '0')
		(*formatt)->flags[4] = 1;
}

void	check_width(char **str, t_flags **formatt)
{
	int res;

	if (**str == '*')
	{
		(*formatt)->width_star = 1;
		(*str)++;
		while (**str && ((**str >= '0' && **str <= '9') || iis(**str)))
			(*str)++;
	}
	else
	{
		res = 0;
		while (**str && ((**str >= '0' && **str <= '9') || iis(**str)))
		{
			if (**str >= '0' && **str <= '9')
				res = (**str - 48) + (res * 10);
			(*str)++;
		}
		(*formatt)->width_len = res;
	}
}

void	check_precision(char **str, t_flags **formatt)
{
	int res;

	(*str)++;
	if (**str == '*')
	{
		(*formatt)->precision_star = 1;
		(*str)++;
		while (**str && ((**str >= '0' && **str <= '9') || iis(**str)))
			(*str)++;
	}
	else
	{
		res = 0;
		while (**str && ((**str >= '0' && **str <= '9') || iis(**str)))
		{
			if (**str >= '0' && **str <= '9')
				res = (**str - 48) + (res * 10);
			(*str)++;
		}
		(*formatt)->precision_len = res;
	}
}

void	check_type(char **str, t_flags **formatt)
{
	if (**str == 'h' && *(*str + 1) == 'h')
		(*formatt)->type = 1;
	if (**str == 'h' && *(*str + 1) != 'h')
		(*formatt)->type = 2;
	if (**str == 'l' && *(*str + 1) == 'l')
		(*formatt)->type = 3;
	if (**str == 'l' && *(*str + 1) != 'l')
		(*formatt)->type = 4;
	if (**str == 'j')
		(*formatt)->type = 5;
	if (**str == 'z')
		(*formatt)->type = 6;
	if ((*formatt)->type == 3 || (*formatt)->type == 1)
		(*str)++;
	(*str)++;
	while (iis(**str))
		(*str)++;
}

t_flags		*ft_format(char **str)
{
	t_flags *formatt;
	char	*tmp;
	char *types = "sSpdDioOuUxXcC%";

	tmp = (*str) - 1;
	init_format(&formatt);
	while (**str && (**str == '-' || **str == '+' || **str == ' ' || **str == '#' || **str == '0'))
			check_flags(*(*str)++, &formatt);
	if ((**str >= '0' && **str <= '9') || **str == '*')
		check_width(&(*str), &formatt);
	if (**str == '.')
		check_precision(&(*str), &formatt);
	if (**str == 'h' || **str == 'l' || **str == 'j' || **str == 'z')
		check_type(&(*str), &formatt);
	while (*types)
		if (*(*str) == *types++)
			break ;
	if (*types == 0)
	{
		while (*(*str) && *(*str) != '%')
			(*str)++;
		ft_putchar(*tmp++);
		while (*tmp != '%' && *tmp)
			ft_putchar(*tmp++);
	}
	return (formatt);
}