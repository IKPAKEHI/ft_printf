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

int	ft_realooctal(char **str, char c, char **to_free)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 1;
	if (!(tmp = (char*)malloc(sizeof(char) * ft_strlen(*str))))
		return (0);
	(tmp)[0] = c;
	while ((*str)[i])
		tmp[j++] = (*str)[i++];
	tmp[j] = 0;
	free(*to_free);
	(*str) = tmp;
	return (1);
}
