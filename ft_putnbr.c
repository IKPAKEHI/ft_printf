/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szverhov <szverhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 18:59:23 by szverhov          #+#    #+#             */
/*   Updated: 2017/11/05 18:35:19 by szverhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	recursion(unsigned int nmbr)
{
	if (nmbr == 0)
		return ;
	recursion(nmbr / 10);
	ft_putchar(nmbr % 10 + 48);
}

void		ft_putnbr(int n)
{
	unsigned int nmbr;

	if (n == -2147483648)
	{
		nmbr = 2147483648;
		ft_putchar('-');
	}
	else if (n < 0)
	{
		ft_putchar('-');
		nmbr = n * -1;
	}
	else if (n == 0)
	{
		ft_putchar('0');
		return ;
	}
	else
		nmbr = n;
	recursion(nmbr);
}
