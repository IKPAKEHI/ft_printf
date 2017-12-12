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

static void		in0(int *i, int *j, int *c)
{
	*i = 0;
	*j = 0;
	*c = 0;
}

static void		in1(char **str, int *i, char c)
{
	while ((*str)[(*i)] == ' ')
		(*i)++;
	(*str)[(*i)++] = '0';
	(*str)[(*i)++] = c;
}

int				ft_make_0x_p(char **str, char c)
{
	int		j;
	int		i;
	int		count_zeros;
	char	*tmp;

	if (!(tmp = (char*)malloc(sizeof(char) * ft_strlen(*str))))
		return (0);
	in0(&i, &j, &count_zeros);
	while ((*str)[i] == ' ')
		i++;
	while ((*str)[i++] == '0')
		count_zeros++;
	count_zeros--;
	while ((*str)[i])
		tmp[j++] = (*str)[i++];
	tmp[j] = 0;
	in0(&i, &j, &j);
	in1(&(*str), &i, c);
	while (count_zeros--)
		(*str)[i++] = '0';
	while (tmp[j])
		(*str)[i++] = tmp[j++];
	free(tmp);
	return (1);
}
