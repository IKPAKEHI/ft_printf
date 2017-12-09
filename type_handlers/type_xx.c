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

static void		in0(long int *a, va_list *l, t_flags **mody, char **n)
{
	if ((*mody)->type == 1)
		*a = (unsigned char)va_arg(*l, long int);
	else if ((*mody)->type == 2)
		*a = (unsigned short)va_arg(*l, long int);
	else if ((*mody)->type == 3)
		*a = (unsigned long long)va_arg(*l, unsigned long long);
	else if ((*mody)->type == 4)
		*a = (unsigned long)va_arg(*l, unsigned long);
	else if ((*mody)->type == 5)
		*a = va_arg(*l, long int);
	else if ((*mody)->type == 6)
		*a = (size_t)va_arg(*l, size_t);
	else
		*a = (unsigned int)va_arg(*l, long int);
	*n =  ft_itoa_base_u(*a, 16, 'a');
	if ((*mody)->precision_len >= 0 && (*mody)->spec_flag == 0)
		(*mody)->flags[4] = 0;
}

static void		in1(char **num, t_flags **mody, char **to_free, long int *a)
{
	if ((*num)[0] == '0' && (*num)[1] == '\0' && (*mody)->spec_flag == 0)
		(*num)++;
	if ((*mody)->flags[1] == 1)
		(*mody)->flags[1] = 0;
	if ((*mody)->flags[3] == 1 && *a != 0)
	{
		ft_realochex(&(*num), 'x', &(*to_free));
		(*mody)->precision_len += 2;
		(*to_free) = (*num);
	}
	if ((*num)[0] == '-')
	{
		(*mody)->flags[1] = 0;
		(*mody)->flags[2] = 0;
	}
	if ((*mody)->flags[0] == 1)
		(*mody)->flags[4] = 0;
	if ((*mody)->flags[4] == 1 && ((*mody)->precision_len > 2))
		(*mody)->flags[4] = 0;
}

static void		in2(int *res_len, t_flags **mody, char **num, char **res)
{
	(*res_len) = (*mody)->precision_len <= (*mody)->width_len ?
	(*mody)->width_len : (*mody)->precision_len;
	if (((*num)[0] == '-' || (*mody)->flags[1] == 1) &&
	(*mody)->precision_len >= (int)ft_strlen((*num)))
	{
		if ((*mody)->width_len <= (*mody)->precision_len)
			(*res_len)++;
		if ((*mody)->flags[1] != 1)
			(*mody)->precision_len++;
	}
	if ((*res_len) < (int)ft_strlen((*num)))
	{
		(*res_len) = ft_strlen((*num));
		if ((*mody)->flags[1] == 1)
			(*res_len)++;
	}
	(*res) = (char*)malloc(sizeof(char) * ((*res_len) + 1));
	(*res)[(*res_len)] = 0;
	(*res_len)--;
	while ((*res_len) != -1)
		(*res)[(*res_len)--] = ' ';
	(*mody)->precision_len -= ft_strlen((*num));
	(*mody)->width_len -= ft_strlen((*num));
}

void			type_x(va_list *list, t_flags **m)
{
	long int	a;
	char		*num;
	int			res_len;
	char		*res;
	char		*to_free;

	in0(&a, list, &(*m), &num);
	to_free = num;
	in1(&num, &(*m), &to_free, &a);
	in2(&res_len, &(*m), &num, &res);
	if ((*m)->precision_len > 0 && (*m)->width_len > 0 &&
	(*m)->width_len > (*m)->precision_len)
		(*m)->width_len -= (*m)->precision_len;
	if ((*m)->flags[4] == 1)
		ft_write_zeros(&res,(*m)->width_len, (*m)->flags[1], a);
	if ((*m)->flags[4] == 0)
		ft_write_spaces(&res,(*m)->width_len, (*m)->flags[0]);
	ft_write_num(&res, num, (*m)->flags[0], (*m)->flags[1]);
	if ((*m)->precision_len > 0)
		write_precison(&res, (*m)->precision_len, ft_strlen(num), (*m)->flags[0]);
	if ((*m)->flags[3] == 1 && ((*m)->flags[4] == 1 || (*m)->precision_len > 0))
		ft_make_0x_p(&res, 'x');
	ft_putstr(res);
	free(to_free);
	free(res);
}
