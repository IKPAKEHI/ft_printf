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

static void		in0(long long int v, unsigned long long int *r, int b, int *n)
{
	if (v < 0)
	{
		if (b == 10)
			(*n) = 1;
		(*r) = v * -1;
	}
	else
		(*r) = v;
}

char	*ft_itoa_base(long long int value, int base)
{
	int						i;
	char					*nbr;
	int						neg;
	unsigned long long int	r;

	neg = 0;
	in0(value, &r, base, &neg);
	nbr = (char*)malloc(sizeof(char) * (i = 25));
	nbr[i + neg] = '\0';
	if (value == 0)
	{
		nbr[0] = '0';
		nbr[1] = '\0';
		return (nbr);
	}
	while (i-- > 0)
	{
		nbr[i + neg] = (r % base) + (r % base > 9 ? 'a' - 10 : '0');
		r = r / base;
	}
	nbr = remove_zeros(&nbr, neg);
	neg == 1 ? (nbr[0] = '-') : 0;
	return (nbr);
}
