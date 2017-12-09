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

void	ft_write_spaces(char **str, int i, int alignment)
{
	int j;

	if (i <= 0)
		return ;
	if (alignment == 0)
	{
		j = 0;
		while (i--)
			(*str)[j++] = ' ';
		return ;
	}
	if (alignment == 1)
	{
		j = ft_strlen(*str) - 1;
		while (i--)
			(*str)[j--] = ' ';
		return ;
	}
}
