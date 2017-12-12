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

static int		in0(t_flags **m, va_list *l, long long int *a, char **n)
{
	if ((*m)->width_len < 0)
	{
		(*m)->width_len *= -1;
		(*m)->flags[0] = 1;
	}
	if ((*m)->type == 5)
		(*a) = (long long int)va_arg(*l, long long int);
	else if ((*m)->type == 6)
		(*a) = (size_t)va_arg(*l, size_t);
	else if ((*m)->type == 1)
		(*a) = (char)va_arg(*l, long int);
	else if ((*m)->type == 2)
		(*a) = (short)va_arg(*l, long int);
	else if ((*m)->type == 3)
		(*a) = (long long int)va_arg(*l, long long int);
	else if ((*m)->type == 4)
		(*a) = (long int)va_arg(*l, long int);
	else
		(*a) = (int)va_arg(*l, int);
	if (!((*n) = ft_itoa_base((*a), 10)))
		return (0);
	((*m)->precision_len >= 0 && (*m)->spec_flag == 0) ?
	((*m)->flags[4] = 0) : 0;
	return (1);
}

static void		in1(t_flags **m, char **n, int *r_l)
{
	if ((*m)->flags[1] == 0 && (*m)->flags[2] == 1 && (*n)[0] != '-')
	{
		ft_putchar(' ');
		if ((*m)->width_len > 0)
			(*m)->width_len--;
		(*m)->flags[2] = 0;
	}
	if ((*n)[0] == '0' && (*n)[1] == '\0' && (*m)->spec_flag == 0)
		(*n)++;
	if ((*n)[0] == '-')
	{
		(*m)->flags[1] = 0;
		(*m)->flags[2] = 0;
	}
	if ((*m)->flags[0] == 1)
		(*m)->flags[4] = 0;
	if ((*m)->flags[4] == 1 && ((*m)->precision_star > 0 ||
	(*m)->precision_len > 0))
		(*m)->flags[4] = 0;
	(*r_l) = (*m)->precision_len <= (*m)->width_len ?
	(*m)->width_len : (*m)->precision_len;
}

static int		in2(t_flags **m, char **n, char **r, int *r_l)
{
	if (((*n)[0] == '-' || (*m)->flags[1] == 1) &&
	(*m)->precision_len >= (int)ft_strlen((*n)))
	{
		((*m)->width_len <= (*m)->precision_len) ? ((*r_l) += 1) : 0;
		((*m)->flags[1] != 1) ? ((*m)->precision_len += 1) : 0;
	}
	if ((*r_l) < (int)ft_strlen((*n)))
	{
		(*r_l) = ft_strlen((*n));
		((*m)->flags[1] == 1 || (*m)->flags[2] == 1) ? ((*r_l) += 1) : 0;
	}
	if (!((*r) = (char*)malloc(sizeof(char) * ((*r_l) + 1))))
		return (0);
	(*r)[(*r_l)--] = 0;
	while ((*r_l) != -1)
		(*r)[(*r_l)--] = ' ';
	(*m)->precision_len -= ft_strlen((*n));
	(*m)->width_len -= ft_strlen((*n));
	if ((*m)->precision_len > 0 && (*m)->width_len > 0 &&
	(*m)->width_len > (*m)->precision_len)
		(*m)->width_len -= (*m)->precision_len;
	return (1);
}

void			type_d(va_list *list, t_flags **mody)
{
	long long int	a;
	char			*num;
	int				res_len;
	char			*res;
	char			*to_free;

	if (!list || !mody || !(*mody) || (in0(&(*mody), list, &a, &num)) == 0)
		return ;
	to_free = num;
	in1(&(*mody), &num, &res_len);
	if ((in2(&(*mody), &num, &res, &res_len)) == 0)
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
