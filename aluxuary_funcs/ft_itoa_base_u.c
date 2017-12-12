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

char	*ft_itoa_base_u(unsigned long int value, int base, char later)
{
	int		i;
	char	*nbr;

	i = 25;
	nbr = (char*)malloc(sizeof(char) * i);
	nbr[i] = '\0';
	if (value == 0)
	{
		nbr[0] = '0';
		nbr[1] = 0;
		return (nbr);
	}
	while (i-- > 0)
	{
		nbr[i] = (value % base) + (value % base > 9 ? later - 10 : '0');
		value = value / base;
	}
	nbr = remove_zeros(&nbr, 0);
	return (nbr);
}
