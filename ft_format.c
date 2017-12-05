
#include "ft_printf.h"





void	write_precison(char **str, int i, int num_len, int alig)
{
	int str_len;
	int minus;
	int a; 
	int j;

	minus = 0;
	if (i <= 0)
			return ;
	if (alig == 0)
	{
		str_len = (int)ft_strlen(*str) - num_len - 1;
		if ((*str)[str_len + 1] == '-')
		{
			minus = 1;
			str_len++;
		}
		if ((*str)[str_len] == '+')
		{
			minus = 2;
		}
		while (i--)
			(*str)[str_len--] = '0';
		if (minus == 1)
			(*str)[str_len] = '-';
		if (minus == 2)
		{
			if (str_len < 0)
				str_len = 0;
			(*str)[str_len] = '+';
		}
		return ;
	}
	if ((*str)[0] == '-' || (*str)[0] == '+')
	{
		j = 1;
		i++;
	}
	else
		j = 0;
	a = ((*str)[0] == '-' || (*str)[0] == '+') ? 1 : 0;
	if ((*str)[0] == '+')
	{
		num_len++;
	}
	ft_memmove((*str) + i, (*str) + a, num_len - a);
	i -= a;
	while(i--)
		(*str)[j++] = '0';
}

void	ft_write_zeros(char **str, int i)
{
	int j;

	if (i <= 0)
		return ;
	j = 0;
	while (i-- > 0)
		(*str)[j++] = '0';
}


void	ft_write_spaces(char **str, int i, int alignment)
{
	int j;

	if (i <= 0)
		return ;
	if (alignment == 0)
	{
		j = 0;
		while (i--)
			(*str)[j++] = ' ';
		return ;
	}
	if (alignment == 1)
	{
		j = (int)ft_strlen(*str) - 1;
		while (i--)
			(*str)[j--] = ' ';
		return ;
	}

}