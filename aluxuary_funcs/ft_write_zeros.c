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

void	ft_write_zeros(char **str, int i, int plus, int minus)
{
	int j;
	int delimit;

	delimit = 0;
	if (i <= 0)
		return ;
	j = 0;
	if (minus < 0)
	{
		(*str)[0] = '-';
		delimit = 1;
		i++;
		j++;
	}
	while (i-- > delimit)
		(*str)[j++] = '0';
	if (plus)
		(*str)[0] = '+';
}
