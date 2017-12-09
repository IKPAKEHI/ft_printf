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

void ft_realooctal(char **str, char c,char **to_free)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = (char*)malloc(sizeof(char) * ft_strlen(*str));
	while ((*str)[i])
		tmp[j++] = (*str)[i++];
	tmp[j] = 0;
	free(*to_free);
	(*str) = (char*)malloc(sizeof(char) * ft_strlen(tmp) + 2);
	i = 1;
	j = 0;
	(*str)[0] = c;
	while (tmp[j])
		(*str)[i++] = tmp[j++];
	(*str)[i] = 0;
	free(tmp);
}
