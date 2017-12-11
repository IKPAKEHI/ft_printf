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

void type_C(va_list *list, t_flags **mody)
{

	wchar_t c;
	int size;
	char res;
	 
	
	//size = ft_wchar_size(c);
	if ((*mody)->precision_len > 0)
	{
		type_c(list, &(*mody));
		return ;
		//size -= (*mody)->precision_len;
	}
	if ((*mody)->precision_len >= size)
	{
		//size = 1;
	}
		//(*mody)->width_len -= ft_wchar_size(c);
	c = va_arg(*list, wchar_t);
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
	// wchar_t c;

	// *mody = *mody;
	// c = va_arg(*list, wchar_t);
	// if ((*mody)->width_star)
	// 	(*mody)->width_len = va_arg(*list, int);
	// if ((*mody)->width_len > 0 && (*mody)->flags[0] == 1)
	// {
	// 	ft_putwchar(c);
	// 	while (--(*mody)->width_len)
	// 		ft_putwchar(' ');
	// 	return ;
	// }
	// if ((*mody)->width_len > 0 & (*mody)->flags[0] != 1)
	// {
	// 	while (--(*mody)->width_len)
	// 		ft_putwchar(' ');
	// 	ft_putwchar(c);
	// 	return ;
	// }
	// ft_putwchar(c);
}
