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

int		ft_wchar_size(wchar_t c)
{
	int res;

	res = 0;
	if (c < 128)
		res += 1;
	if (c > 127 && c < 2048)
		res += 2;
	if (c > 2047 && c < 65536)
		res += 3;
	if (c > 65535 && c < 2097152)
		res += 4;
	return (res);
}

void	type_cu(va_list *list, t_flags **mody)
{
	wchar_t c;

	if (mody == 0)
		return ;
	c = va_arg(*list, wchar_t);
	(*mody)->width_len -= ft_wchar_size(c);
	if ((*mody)->width_len > 0 && (*mody)->flags[0] == 1)
	{
		ft_putwchar(c);
		while ((*mody)->width_len--)
			ft_putwchar(' ');
		return ;
	}
	if ((*mody)->width_len > 0 & (*mody)->flags[0] != 1)
	{
		while ((*mody)->width_len--)
			ft_putwchar(' ');
		ft_putwchar(c);
		return ;
	}
	ft_putwchar(c);
}
