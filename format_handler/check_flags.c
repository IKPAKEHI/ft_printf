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

void	check_flags(char c, t_flags **formatt)
{
	if (c == '-')
		(*formatt)->flags[0] = 1;
	if (c == '+')
		(*formatt)->flags[1] = 1;
	if (c == ' ')
		(*formatt)->flags[2] = 1;
	if (c == '#')
		(*formatt)->flags[3] = 1;
	if (c == '0')
		(*formatt)->flags[4] = 1;
}
