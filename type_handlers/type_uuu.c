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

static int		i(t_flags **m, char **n, va_list *l, unsigned long long int *a)
{
	if ((*m)->type == 1)
		(*a) = (unsigned short)va_arg(*l, unsigned long long int);
	else if ((*m)->type == 2)
		(*a) = (unsigned long)va_arg(*l, unsigned long long int);
	else if ((*m)->type == 3)
		(*a) = (unsigned long long int)va_arg(*l, unsigned long long int);
	else if ((*m)->type == 4)
		(*a) = (unsigned long int)va_arg(*l, unsigned long long int);
	else if ((*m)->type == 5)
		(*a) = (unsigned long long int)va_arg(*l, unsigned long long int);
	else if ((*m)->type == 6)
		(*a) = (size_t)va_arg(*l, unsigned long long int);
	else
		(*a) = (unsigned long)va_arg(*l, unsigned long);
	if (!((*n) = ft_itoa_base_u((*a), 10, 'a')))
		return (0);
	if ((*m)->precision_len >= 0 && (*m)->spec_flag == 0)
	{
		(*m)->flags[4] = 0;
		(*m)->flags[1] = 0;
	}
	return (1);
}

static void		in1(t_flags **mody, char **num, int *r_l)
{
	if ((*num)[0] == '0' && (*num)[1] == '\0' && (*mody)->spec_flag == 0)
		(*num)++;
	if ((*num)[0] == '-')
		(*mody)->flags[2] = 0;
	if ((*mody)->flags[0] == 1)
		(*mody)->flags[4] = 0;
	if ((*mody)->flags[4] == 1 && ((*mody)->precision_star > 0 ||
	(*mody)->precision_len > 0))
		(*mody)->flags[4] = 0;
	(*r_l) = (*mody)->precision_len <= (*mody)->width_len ?
	(*mody)->width_len : (*mody)->precision_len;
	if (((*num)[0] == '-' || (*mody)->flags[1] == 1) &&
	(*mody)->precision_len >= (int)ft_strlen((*num)))
	{
		if ((*mody)->width_len <= (*mody)->precision_len)
			(*r_l)++;
		if ((*mody)->flags[1] != 1)
			(*mody)->precision_len++;
	}
	if ((*r_l) < (int)ft_strlen((*num)))
	{
		(*r_l) = ft_strlen((*num));
		if ((*mody)->flags[1] == 1)
			(*r_l)++;
	}
}

static void		in2(t_flags **mody, char **num, char **res, int *r_l)
{
	while ((*r_l) != -1)
		(*res)[(*r_l)--] = ' ';
	(*mody)->precision_len -= ft_strlen((*num));
	(*mody)->width_len -= ft_strlen((*num));
	if ((*mody)->precision_len > 0 && (*mody)->width_len > 0 &&
	(*mody)->width_len > (*mody)->precision_len)
		(*mody)->width_len -= (*mody)->precision_len;
}

void			type_uuu(va_list *list, t_flags **mody)
{
	unsigned long long int	a;
	char					*num;
	int						res_len;
	char					*res;
	char					*to_free;

	if (!list || !mody || !(*mody) || !(i(&(*mody), &num, list, &a)))
		return ;
	to_free = num;
	in1(&(*mody), &num, &res_len);
	if (!(res = (char*)malloc(sizeof(char) * (res_len + 1))))
		return ;
	res[res_len--] = 0;
	in2(&(*mody), &num, &res, &res_len);
	if ((*mody)->flags[4] == 1)
		ft_write_zeros(&res, (*mody)->width_len, (*mody)->flags[1], 1);
	if ((*mody)->flags[4] == 0)
		ft_write_spaces(&res, (*mody)->width_len, (*mody)->flags[0]);
	ft_write_num(&res, num, (*mody)->flags[0], (*mody)->flags[1]);
	if ((*mody)->precision_len > 0)
		write_precison(&res, (*mody)->precision_len,
		ft_strlen(num), (*mody)->flags[0]);
	ft_putstr(res);
	free(res);
	free(to_free);
}
