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

static void		in0(t_flags **m, char **tmp, int *r_l)
{
	if ((*m)->flags[1] == 1)
		(*m)->flags[1] = 0;
	if ((*m)->flags[0] == 1)
		(*m)->flags[4] = 0;
	if ((*m)->flags[4] == 1 && ((*m)->precision_star > 0 ||
	(*m)->precision_len > 0))
		(*m)->flags[4] = 0;
	if ((*tmp)[0] == '\0')
		(*m)->precision_len = 0;
	(*r_l) = (*m)->precision_len <= (*m)->width_len ?
	(*m)->width_len : (*m)->precision_len;
	if ((*m)->precision_len >= 0 &&
	(*m)->precision_len < (int)ft_strlen((*tmp)))
		write_precison_str(&(*tmp), &(*m), (int)ft_strlen((*tmp)));
	if (((*tmp)[0] == '-' || (*m)->flags[1] == 1) &&
	(*m)->precision_len >= (int)ft_strlen((*tmp)))
	{
		(*m)->width_len <= (*m)->precision_len ? (*r_l) += 1 : 0;
		(*m)->flags[1] != 1 ? (*m)->precision_len += 1 : 0;
	}
	if ((*r_l) < (int)ft_strlen((*tmp)))
	{
		(*r_l) = ft_strlen((*tmp));
		(*m)->flags[1] == 1 ? (*r_l) += 1 : 0;
	}
}

void			type_error(char *tmp, t_flags **mody)
{
	int		res_len;
	char	*res;

	if (tmp == 0)
	{
		ft_putstr("(null)");
		return ;
	}
	in0(&(*mody), &tmp, &res_len);
	if (!(res = (char*)malloc(sizeof(char) * (res_len + 1))))
		return ;
	res[res_len--] = 0;
	while (res_len != -1)
		res[res_len--] = ' ';
	(*mody)->width_len -= ft_strlen(tmp);
	if ((*mody)->flags[4] == 0)
		ft_write_spaces(&res, (*mody)->width_len, (*mody)->flags[0]);
	if ((*mody)->flags[4] == 1)
		ft_write_zeros(&res, (*mody)->width_len, (*mody)->flags[0], 0);
	ft_write_num(&res, tmp, (*mody)->flags[0], (*mody)->flags[1]);
	if (!(g_str = ft_strjoin(g_str, res)))
		return ;
	free(tmp);
	ft_putgstr();
}
