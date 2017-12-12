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

static int		in0(t_flags **m, va_list *l, char **n, unsigned long int *a)
{
	if ((*m)->type == 1)
		(*a) = (unsigned short)va_arg(*l, unsigned long int);
	else if ((*m)->type == 2)
		(*a) = (unsigned short)va_arg(*l, unsigned long int);
	else if ((*m)->type == 3)
		(*a) = (unsigned long long)va_arg(*l, unsigned long long);
	else if ((*m)->type == 4)
		(*a) = (unsigned long)va_arg(*l, unsigned long);
	else if ((*m)->type == 5)
		(*a) = va_arg(*l, unsigned long int);
	else if ((*m)->type == 6)
		(*a) = (size_t)va_arg(*l, size_t);
	else
		(*a) = (unsigned long int)va_arg(*l, unsigned long int);
	if (!((*n) = ft_itoa_base_u((*a), 8, 'a')))
		return (0);
	if ((*m)->precision_len >= 0 && (*m)->spec_flag == 0)
		(*m)->flags[4] = 0;
	if ((*m)->flags[1] == 1)
		(*m)->flags[1] = 0;
	return (1);
}

static int		in1(t_flags **mody, char **num, char **to_free, int *r_l)
{
	if ((*num)[1] != '\0')
		while (*(*num) == '0')
			(*num)++;
	if ((*num)[0] == '0' && (*num)[1] == '\0' &&
		(*mody)->spec_flag == 0 && (*mody)->flags[3] != 1)
		(*num)++;
	if ((*mody)->flags[3] == 1 && (*num)[0] != '0')
	{
		if ((ft_realooctal(&(*num), '0', &(*to_free))) == 0)
			return (0);
		(*to_free) = (*num);
	}
	if ((*num)[0] == '-')
	{
		(*mody)->flags[1] = 0;
		(*mody)->flags[2] = 0;
	}
	if ((*mody)->flags[0] == 1)
		(*mody)->flags[4] = 0;
	if ((*mody)->flags[4] == 1 && ((*mody)->precision_star > 0 ||
	(*mody)->precision_len > 0))
		(*mody)->flags[4] = 0;
	(*r_l) = (*mody)->precision_len <= (*mody)->width_len ?
	(*mody)->width_len : (*mody)->precision_len;
	return (1);
}

static int		in2(t_flags **m, char **num, char **res, int *r_l)
{
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
		((*m)->flags[1] == 1) ? (*r_l) += 1 : 0;
	}
	if (!((*res) = (char*)malloc(sizeof(char) * ((*r_l) + 1))))
		return (0);
	(*res)[(*r_l)] = 0;
	(*r_l)--;
	while ((*r_l) != -1)
		(*res)[(*r_l)--] = ' ';
	(*m)->precision_len -= ft_strlen((*num));
	(*m)->width_len -= ft_strlen((*num));
	if ((*m)->precision_len > 0 && (*m)->width_len > 0 &&
	(*m)->width_len > (*m)->precision_len)
		(*m)->width_len -= (*m)->precision_len;
	return (1);
}

void			type_ou(va_list *list, t_flags **mody)
{
	unsigned long int	a;
	char				*num;
	int					res_len;
	char				*res;
	char				*to_free;

	if (!list || !mody || !(*mody) || !(in0(&(*mody), list, &num, &a)))
		return ;
	to_free = num;
	if (!(in1(&(*mody), &num, &to_free, &res_len)))
		return ;
	if (!(in2(&(*mody), &num, &res, &res_len)))
		return ;
	if ((*mody)->flags[4] == 1)
		ft_write_zeros(&res, (*mody)->width_len, (*mody)->flags[1], a);
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
