/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szverhov <szverhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 18:54:24 by szverhov          #+#    #+#             */
/*   Updated: 2017/10/30 12:15:13 by szverhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static	void	in0(int *i, int *j, char **str)
{
	if ((*str)[0] == '-' || (*str)[0] == '+')
	{
		(*j) = 1;
		(*i)++;
	}
	else
		(*j) = 0;
}

static void		in1(int *j, char **str, int *n_l, int *i)
{
	int a;

	a = ((*str)[0] == '-' || (*str)[0] == '+') ? 1 : 0;
	((*str)[0] == '+') ? ((*n_l) += 1) : 0;
	ft_memmove((*str) + (*i), (*str) + a, (*n_l) - a);
	(*i) -= a;
	while ((*i)--)
		(*str)[(*j)++] = '0';
}

void			write_precison(char **str, int i, int num_len, int alig)
{
	int str_len;
	int minus;
	int j;

	minus = 0;
	if (i <= 0)
		return ;
	if (alig == 0)
	{
		str_len = ft_strlen(*str) - num_len - 1;
		((*str)[str_len + 1] == '-' && (minus = 1)) ? (str_len += 1) : 0;
		((*str)[str_len] == '+') ? (minus = 2) : 0;
		while (i--)
			(*str)[str_len--] = '0';
		(minus == 1) ? ((*str)[str_len] = '-') : 0;
		if (minus == 2)
		{
			(str_len < 0) ? (str_len = 0) : 0;
			(*str)[str_len] = '+';
		}
		return ;
	}
	in0(&i, &j, &(*str));
	in1(&j, &(*str), &num_len, &i);
}
