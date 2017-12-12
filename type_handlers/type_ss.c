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

static void		in0(t_flags **mody, char **tmp, va_list *list)
{
	(*tmp) = ft_strdup(va_arg(*list, char*));
	if ((*mody)->precision_len == 0 && (*mody)->spec_flag == 0)
	{
		free((*tmp));
		(*tmp) = ft_strdup("");
	}
}

static void		in1(t_flags **m, char **tmp, int *r_l)
{
	(*m)->precision_len > (int)ft_strlen((*tmp)) ?
	((*m)->precision_len) = 0 : 0;
	(*m)->flags[1] == 1 ? ((*m)->flags[1] = 0) : 0;
	(*m)->flags[0] == 1 ? ((*m)->flags[4] = 0) : 0;
	(*m)->flags[4] == 1 && ((*m)->precision_star > 0 ||
	(*m)->precision_len > 0) ? ((*m)->flags[4] = 0) : 0;
	(*tmp)[0] == '\0' ? ((*m)->precision_len = 0) : 0;
	if ((*m)->precision_len >= 0 &&
	(*m)->precision_len < (int)ft_strlen((*tmp)))
		write_precison_str(&(*tmp), &(*m), (int)ft_strlen((*tmp)));
	(*r_l) = (*m)->precision_len <= (*m)->width_len ?
	(*m)->width_len : (*m)->precision_len;
	if (((*tmp)[0] == '-' || (*m)->flags[1] == 1) &&
	(*m)->precision_len >= (int)ft_strlen((*tmp)))
	{
		(*m)->width_len <= (*m)->precision_len ? ((*r_l) += 1) : 0;
		(*m)->flags[1] != 1 ? ((*m)->precision_len += 1) : 0;
	}
	if ((*r_l) < (int)ft_strlen((*tmp)))
	{
		(*r_l) = ft_strlen((*tmp));
		(*m)->flags[1] == 1 ? ((*r_l) += 1) : 0;
	}
}

static void		in2(t_flags **mody, char **res, int *r_l)
{
	while ((*r_l) != -1)
		(*res)[(*r_l)--] = ' ';
	if ((*mody)->flags[4] == 0)
		ft_write_spaces(&(*res), (*mody)->width_len, (*mody)->flags[0]);
	if ((*mody)->flags[4] == 1)
		ft_write_zeros(&(*res), (*mody)->width_len, (*mody)->flags[0], 0);
}

void			type_s(va_list *list, t_flags **mody)
{
	char	*tmp;
	int		res_len;
	char	*res;

	if ((*mody)->type == 4 || !list || !mody || !(*mody))
	{
		type_su(list, &(*mody));
		return ;
	}
	in0(&*(mody), &tmp, list);
	if (tmp == 0)
	{
		ft_putstr("(null)");
		return ;
	}
	in1(&(*mody), &tmp, &res_len);
	if (!(res = (char*)malloc(sizeof(char) * (res_len + 1))))
		return ;
	res[res_len--] = 0;
	in2(&(*mody), &res, &res_len);
	ft_write_num(&res, tmp, (*mody)->flags[0], (*mody)->flags[1]);
	ft_putstr(res);
	free(res);
	free(tmp);
}
