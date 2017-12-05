/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szverhov <szverhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 14:31:43 by szverhov          #+#    #+#             */
/*   Updated: 2017/11/03 12:26:48 by szverhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
