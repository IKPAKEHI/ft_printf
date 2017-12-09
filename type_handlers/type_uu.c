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

static void		i(t_flags **m, char **n, va_list *l, unsigned long long int *a)
{
	if ((*m)->type == 1)
		(*a) = (unsigned char)va_arg(*l, unsigned long long int);
	else if ((*m)->type == 2)
		(*a) = (unsigned short)va_arg(*l, unsigned long long int);
	else if ((*m)->type == 3)
		(*a) = (unsigned long long int)va_arg(*l, unsigned long long int);
	else if ((*m)->type == 4)
		(*a) = (unsigned long int)va_arg(*l, unsigned long long int);
	else if ((*m)->type == 5)
		(*a) = (unsigned long long int)va_arg(*l, unsigned long long int);
	else if ((*m)->type == 6)
		(*a) = (size_t)va_arg(*l, unsigned long long int);
	else
		(*a) = (unsigned int)va_arg(*l, unsigned int);
	(*n) = ft_itoa_base_u((*a), 10, 'a');
	(*m)->flags[1] = 0;
	if ((*m)->precision_len >= 0 && (*m)->spec_flag == 0)
		(*m)->flags[4] = 0;
}

static void		in1(t_flags **m, char **num, int *r_l)
{
	if ((*num)[0] == '0' && num[1] == '\0' && (*m)->spec_flag == 0)
		(*num)++;
	if ((*num)[0] == '-')
		(*m)->flags[2] = 0;
	if ((*m)->flags[0] == 1)
		(*m)->flags[4] = 0;
	if ((*m)->flags[4] == 1 && ((*m)->precision_star > 0
		|| (*m)->precision_len > 0))
		(*m)->flags[4] = 0;
	(*r_l) = (*m)->precision_len <= (*m)->width_len ?
	(*m)->width_len : (*m)->precision_len;
	if (((*num)[0] == '-' || (*m)->flags[1] == 1) &&
	(*m)->precision_len >= (int)ft_strlen((*num)))
	{
		if ((*m)->width_len <= (*m)->precision_len)
			(*r_l)++;
		if ((*m)->flags[1] != 1)
			(*m)->precision_len++;
	}
	if ((*r_l) < (int)ft_strlen((*num)))
	{
		(*r_l) = ft_strlen((*num));
		if ((*m)->flags[1] == 1)
			(*r_l)++;
	}	
}

static void		in2(char **r, t_flags **mody, char **n, int *r_l)
{
	(*r) = (char*)malloc(sizeof(char) * ((*r_l) + 1));
	(*r)[(*r_l)] = 0;
	(*r_l)--;
	while ((*r_l) != -1)
		(*r)[(*r_l)--] = ' ';
	(*mody)->precision_len -= ft_strlen((*n));
	(*mody)->width_len -= ft_strlen((*n));
	if ((*mody)->precision_len > 0 && (*mody)->width_len > 0 &&
	(*mody)->width_len > (*mody)->precision_len)
		(*mody)->width_len -= (*mody)->precision_len;	
}

void			type_u(va_list *list, t_flags **mody)
{
	unsigned long long int	a;
	char					*num;
	int						res_len;
	char					*res;
	char					*to_free;

	i(&(*mody), &num, list, &a);
	to_free = num;
	in1(&(*mody), &num, &res_len);
	in2(&res, &(*mody), &num, &res_len);
	if ((*mody)->flags[4] == 1)
		ft_write_zeros(&res,(*mody)->width_len, (*mody)->flags[1], 1);
	if ((*mody)->flags[4] == 0)
		ft_write_spaces(&res,(*mody)->width_len, (*mody)->flags[0]);
	ft_write_num(&res, num, (*mody)->flags[0], (*mody)->flags[1]);
	if ((*mody)->precision_len > 0)
		write_precison(&res, (*mody)->precision_len,
		ft_strlen(num), (*mody)->flags[0]);
	ft_putstr(res);
	free(to_free);
	free(res);
}