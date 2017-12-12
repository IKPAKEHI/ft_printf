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

void	in0(t_flags **mody, char *filler)
{
	*filler = ' ';
	if ((*mody)->width_len < 0)
	{
		(*mody)->width_len *= -1;
		(*mody)->flags[0] = 1;
	}
}

void	in1(t_flags **mody, char *filler, char c)
{
	if ((*mody)->flags[4] == 1)
		*filler = '0';
	while (--(*mody)->width_len)
		ft_putchar(*filler);
	ft_putchar(c);
}

void	type_c(va_list *list, t_flags **mody)
{
	char	c;
	char	filler;

	in0(&(*mody), &filler);
	if ((*mody)->type == 4)
	{
		type_cu(list, &(*mody));
		return ;
	}
	c = va_arg(*list, long long);
	if ((*mody)->width_len > 0 && (*mody)->flags[0] == 1)
	{
		ft_putchar(c);
		while (--(*mody)->width_len)
			ft_putchar(filler);
		return ;
	}
	if ((*mody)->width_len > 0 & (*mody)->flags[0] != 1)
	{
		in1(&(*mody), &filler, c);
		return ;
	}
	ft_putchar(c);
}
