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

static void		in0(t_flags **mody, char **num, va_list *l, long int *a)
{
	if ((*mody)->type == 1)
		(*a) = (unsigned char)va_arg(*l, long int);
	else if ((*mody)->type == 2)
		(*a) = (unsigned short)va_arg(*l, long int);
	else if ((*mody)->type == 3)
		(*a) = (unsigned long long)va_arg(*l, unsigned long long);
	else if ((*mody)->type == 4)
		(*a) = (unsigned long)va_arg(*l, unsigned long);
	else if ((*mody)->type == 5)
		(*a) = va_arg(*l, long int);
	else if ((*mody)->type == 6)
		(*a) = (size_t)va_arg(*l, size_t);
	else
		(*a) = (unsigned int)va_arg(*l, long int);
	(*num) =  ft_itoa_base_u((*a), 16, 'A');
	if ((*mody)->precision_len >= 0 && (*mody)->spec_flag == 0)
		(*mody)->flags[4] = 0;
}

static void		in1(t_flags **m, char **n, int *r_l, char **to_free)
{
	if ((*n)[0] == '0' && (*n)[1] == '\0' && (*m)->spec_flag == 0)
		(*n)++;
	if ((*m)->flags[1] == 1)
		(*m)->flags[1] = 0;
	if ((*m)->flags[3] == 1 && (*n)[1] != '\0')
	{
		ft_realochex(&(*n), 'X', &(*to_free));
		(*m)->precision_len += 2;
		(*to_free) = (*n);
		(*m)->precision_len += 2;
	}
	if ((*n)[0] == '-')
	{
		(*m)->flags[1] = 0;
		(*m)->flags[2] = 0;
	}
	if ((*m)->flags[0] == 1)
		(*m)->flags[4] = 0;
	if ((*m)->flags[4] == 1 && ((*m)->precision_len > 2))
		(*m)->flags[4] = 0;
	(*r_l) = (*m)->precision_len <= (*m)->width_len ?
	(*m)->width_len : (*m)->precision_len;
}

static void		in2(t_flags **m, char **n, char **r, int *r_l)
{
	if (((*n)[0] == '-' || (*m)->flags[1] == 1) &&
	(*m)->precision_len >= (int)ft_strlen((*n)))
	{
		if ((*m)->width_len <= (*m)->precision_len)
			(*r_l)++;
		if ((*m)->flags[1] != 1)
			(*m)->precision_len++;
	}
	if ((*r_l) < (int)ft_strlen((*n)))
	{
		(*r_l) = ft_strlen((*n));
		if ((*m)->flags[1] == 1)
			(*r_l)++;
	}
	(*r) = (char*)malloc(sizeof(char) * ((*r_l) + 1));
	(*r)[(*r_l)] = 0;
	(*r_l)--;
	while ((*r_l) != -1)
		(*r)[(*r_l)--] = ' ';
	(*m)->precision_len -= ft_strlen((*n));
	(*m)->width_len -= ft_strlen((*n));
	if ((*m)->precision_len > 0 && (*m)->width_len > 0 &&
	(*m)->width_len > (*m)->precision_len)
		(*m)->width_len -= (*m)->precision_len;
}

void			type_X(va_list *list, t_flags **mody)
{
	long int	a;
	char		*num;
	int			res_len;
	char		*res;
	char		*to_free;

	in0(&(*mody), &num, list, &a);
	to_free = num;
	in1(&(*mody), &num, &res_len, &to_free);
	in2(&(*mody), &num, &res, &res_len);
	if ((*mody)->flags[4] == 1)
		ft_write_zeros(&res,(*mody)->width_len, (*mody)->flags[1], a);
	if ((*mody)->flags[4] == 0)
		ft_write_spaces(&res,(*mody)->width_len, (*mody)->flags[0]);
	ft_write_num(&res, num, (*mody)->flags[0], (*mody)->flags[1]);
	if ((*mody)->precision_len > 0)
		write_precison(&res, (*mody)->precision_len,
		ft_strlen(num), (*mody)->flags[0]);
	if ((*mody)->flags[3] == 1 && ((*mody)->flags[4] == 1 ||
	(*mody)->precision_len > 0))
		ft_make_0x_p(&res, 'X');
	ft_putstr(res);
	free(to_free);
	free(res);
}
