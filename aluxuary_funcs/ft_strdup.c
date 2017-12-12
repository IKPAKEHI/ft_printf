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

char	*ft_strdup(const char *s1)
{
	char	*res;
	int		i;
	int		j;

	if (s1 == 0)
		return (0);
	i = -1;
	res = (char*)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (res == NULL)
		return (NULL);
	j = 0;
	while (s1[j] != 0)
	{
		res[++i] = s1[j++];
	}
	res[++i] = 0;
	return (res);
}
