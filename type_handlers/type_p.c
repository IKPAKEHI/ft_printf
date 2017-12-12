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

static void		in0(t_flags **m, char **n, int *r_l)
{
	if ((*m)->precision_len >= 0 && (*m)->spec_flag == 0)
		(*m)->flags[4] = 0;
	if ((*n)[0] == '-')
	{
		(*m)->flags[1] = 0;
		(*m)->flags[2] = 0;
	}
	if ((*m)->flags[0] == 1)
		(*m)->flags[4] = 0;
	if ((*m)->flags[4] == 1 && ((*m)->precision_star > 0 ||
	(*m)->precision_len > 2))
		(*m)->flags[4] = 0;
	(*r_l) = (*m)->precision_len <= (*m)->width_len ?
	(*m)->width_len : (*m)->precision_len;
	if (((*n)[0] == '-' || (*m)->flags[1] == 1) &&
	(*m)->precision_len >= (int)ft_strlen((*n)))
	{
		if ((*m)->width_len <= (*m)->precision_len)
			(*r_l)++;
		if ((*m)->flags[1] != 1)
			(*m)->precision_len++;
	}
}

static int		in1(t_flags **m, char **res, char **num, int *r_l)
{
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
	if ((*m)->flags[4] == 1)
		ft_write_zeros(&(*res), (*m)->width_len, (*m)->flags[1], 1);
	if ((*m)->flags[4] == 0)
		ft_write_spaces(&(*res), (*m)->width_len, (*m)->flags[0]);
	ft_write_num(&(*res), (*num), (*m)->flags[0], (*m)->flags[1]);
	if ((*m)->precision_len > 0)
		write_precison(&(*res), (*m)->precision_len,
		ft_strlen((*num)), (*m)->flags[0]);
	return (1);
}

void			type_p(va_list *list, t_flags **mody)
{
	char	*num;
	int		res_len;
	char	*res;
	char	*to_free;

	if ((*mody)->flags[1] == 1)
		(*mody)->flags[1] = 0;
	if (!list || !mody || !(*mody) ||
	!(num = ft_itoa_base(va_arg(*list, long long int), 16)))
		return ;
	to_free = num;
	(*mody)->precision_len += 2;
	if (num[0] == '0' && num[1] == '\0' && (*mody)->spec_flag == 0)
		num++;
	if (!(ft_realochex(&num, 'x', &to_free)))
		return ;
	to_free = num;
	in0(&(*mody), &num, &res_len);
	if (!(in1(&(*mody), &res, &num, &res_len)))
		return ;
	if (!(ft_make_0x_p(&res, 'x')))
		return ;
	ft_putstr(res);
	free(res);
	free(to_free);
}
