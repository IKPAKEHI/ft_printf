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

void	ft_write_num(char **res, char *num, int alignment, int plus)
{
	int		i;
	int		j;

	i = 0;
	if (num[0] == '\0')
		return ;
	if (alignment == 1)
	{
		j = plus == 1 ? 1 : 0;
		(*res)[0] = (plus == 1) ? '+' : ' ';
		while (num[i])
			(*res)[j++] = num[i++];
	}
	if (alignment == 0)
	{
		j = ft_strlen(*res) - 1;
		i = ft_strlen(num) - 1;
		while (i > 0)
			(*res)[j--] = num[i--];
		if ((*res)[0] != '-')
			(*res)[j] = num[i];
		if (plus == 1 && res[0][0] != '+')
			(*res)[--j] = '+';
	}
}
