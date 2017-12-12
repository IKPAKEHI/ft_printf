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

int		ft_realoc_str(char **str, int len)
{
	char	*tmp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if ((*str) == 0 || str == 0)
		return (0);
	if (!(tmp = (char*)malloc(sizeof(char) * (ft_strlen(*str) + len + 1))))
		return (0);
	while ((*str)[j])
		tmp[i++] = (*str)[j++];
	tmp[i] = 0;
	free((*str));
	(*str) = tmp;
	return (1);
}
