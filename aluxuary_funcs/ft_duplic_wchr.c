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

wchar_t	*ft_duplic_wchr(wchar_t *str)
{
	int		i;
	wchar_t	*res;

	if (str == 0)
		return (0);
	i = 0;
	if (!(res = (wchar_t*)malloc(sizeof(wchar_t) * ft_wstrlen(str) + 4)))
		return (0);
	while (*str)
		res[i++] = *str++;
	res[i] = 0;
	return (res);
}
