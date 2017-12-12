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

char	*remove_zeros(char **str, int neg)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = (char*)malloc(sizeof(char) * 25);
	if (neg == 1)
	{
		new[i++] = ' ';
		while ((*str)[++j] == '0')
			;
		while ((*str)[j])
			new[i++] = (*str)[j++];
		new[i] = 0;
		free(*str);
		return (new);
	}
	while ((*str)[j] == '0')
		j++;
	while ((*str)[j])
		new[i++] = (*str)[j++];
	new[i] = 0;
	free(*str);
	return (new);
}
