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

void	type_interest(va_list *list, t_flags **mody)
{
	char	*res;
	int		res_len;
	char	filler;

	filler = ' ';
	if (list == 0)
		return ;
	res_len = (*mody)->width_len == 0 ? 1 : (*mody)->width_len;
	if (!(res = (char*)malloc(sizeof(char) * res_len + 1)))
		return ;
	res[res_len] = 0;
	if ((*mody)->flags[0] == 1)
	{
		res[0] = '%';
		while (res_len != 1)
			res[--res_len] = filler;
		ft_putstr(res);
		return ;
	}
	filler = ((*mody)->flags[4] == 1) ? '0' : ' ';
	res[--res_len] = '%';
	while (res_len)
		res[--res_len] = filler;
	ft_putstr(res);
	free(res);
}
