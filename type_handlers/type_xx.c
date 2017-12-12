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

static int		in0(long int *a, va_list *l, t_flags **m, char **n)
{
	if ((*m)->type == 1)
		*a = (unsigned char)va_arg(*l, long int);
	else if ((*m)->type == 2)
		*a = (unsigned short)va_arg(*l, long int);
	else if ((*m)->type == 3)
		*a = (unsigned long long)va_arg(*l, unsigned long long);
	else if ((*m)->type == 4)
		*a = (unsigned long)va_arg(*l, unsigned long);
	else if ((*m)->type == 5)
		*a = va_arg(*l, long int);
	else if ((*m)->type == 6)
		*a = (size_t)va_arg(*l, size_t);
	else
		*a = (unsigned int)va_arg(*l, long int);
	if (!(*n = ft_itoa_base_u(*a, 16, 'a')))
		return (0);
	if ((*m)->precision_len >= 0 && (*m)->spec_flag == 0)
		(*m)->flags[4] = 0;
	return (1);
}

static int		in1(char **num, t_flags **m, char **to_free, long int *a)
{
	if ((*num)[0] == '0' && (*num)[1] == '\0' && (*m)->spec_flag == 0)
		(*num)++;
	if ((*m)->flags[1] == 1)
		(*m)->flags[1] = 0;
	if ((*m)->flags[3] == 1 && *a != 0)
	{
		if (!(ft_realochex(&(*num), 'x', &(*to_free))))
			return (0);
		(*m)->precision_len += 2;
		(*to_free) = (*num);
	}
	if ((*num)[0] == '-')
	{
		(*m)->flags[1] = 0;
		(*m)->flags[2] = 0;
	}
	if ((*m)->flags[0] == 1)
		(*m)->flags[4] = 0;
	if ((*m)->flags[4] == 1 && ((*m)->precision_len > 2))
		(*m)->flags[4] = 0;
	return (1);
}

static int		in2(int *res_len, t_flags **m, char **num, char **res)
{
	(*res_len) = (*m)->precision_len <= (*m)->width_len ?
	(*m)->width_len : (*m)->precision_len;
	if (((*num)[0] == '-' || (*m)->flags[1] == 1) &&
	(*m)->precision_len >= (int)ft_strlen((*num)))
	{
		((*m)->width_len <= (*m)->precision_len) ? ((*res_len) += 1) : 0;
		((*m)->flags[1] != 1) ? ((*m)->precision_len += 1) : 0;
	}
	if ((*res_len) < (int)ft_strlen((*num)))
	{
		(*res_len) = ft_strlen((*num));
		((*m)->flags[1] == 1) ? ((*res_len) += 1) : 0;
	}
	if (!((*res) = (char*)malloc(sizeof(char) * ((*res_len) + 1))))
		return (0);
	(*res)[(*res_len)--] = 0;
	while ((*res_len) != -1)
		(*res)[(*res_len)--] = ' ';
	(*m)->precision_len -= ft_strlen((*num));
	(*m)->width_len -= ft_strlen((*num));
	if ((*m)->precision_len > 0 && (*m)->width_len > (*m)->precision_len)
		(*m)->width_len -= (*m)->precision_len;
	if ((*m)->flags[4] == 0)
		ft_write_spaces(&(*res), (*m)->width_len, (*m)->flags[0]);
	return (1);
}

void			type_x(va_list *list, t_flags **m)
{
	long int	a;
	char		*num;
	int			res_len;
	char		*res;
	char		*to_free;

	if (!(in0(&a, list, &(*m), &num)))
		return ;
	to_free = num;
	if (!(in1(&num, &(*m), &to_free, &a)))
		return ;
	if (!(in2(&res_len, &(*m), &num, &res)))
		return ;
	if ((*m)->flags[4] == 1)
		ft_write_zeros(&res, (*m)->width_len, (*m)->flags[1], a);
	ft_write_num(&res, num, (*m)->flags[0], (*m)->flags[1]);
	if ((*m)->precision_len > 0)
		write_precison(&res, (*m)->precision_len,
		ft_strlen(num), (*m)->flags[0]);
	if ((*m)->flags[3] == 1 && ((*m)->flags[4] == 1 || (*m)->precision_len > 0))
		if (!(ft_make_0x_p(&res, 'x')))
			return ;
	ft_putstr(res);
	free(to_free);
	free(res);
}
