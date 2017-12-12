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

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char *ds;

	ds = (unsigned char*)dst;
	if (dst > src)
	{
		while (len--)
			*((unsigned char*)dst + len) = *((unsigned char*)src + len);
	}
	else
	{
		while (len--)
		{
			*((unsigned char*)dst) = *((unsigned char*)src);
			dst++;
			src++;
		}
	}
	return (ds);
}
