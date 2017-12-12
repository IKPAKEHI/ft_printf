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

void	check_type(const char **str, t_flags **formatt)
{
	if (**str == 'h' && *(*str + 1) == 'h' && 1 > (*formatt)->type)
		(*formatt)->type = 1;
	if (**str == 'h' && *(*str + 1) != 'h' && 2 > (*formatt)->type)
		(*formatt)->type = 2;
	if (**str == 'l' && *(*str + 1) == 'l' && 3 > (*formatt)->type)
		(*formatt)->type = 3;
	if (**str == 'l' && *(*str + 1) != 'l' && 4 > (*formatt)->type)
		(*formatt)->type = 4;
	if (**str == 'j' && 5 > (*formatt)->type)
		(*formatt)->type = 5;
	if (**str == 'z' && 6 > (*formatt)->type)
		(*formatt)->type = 6;
	if ((*formatt)->type == 3 || (*formatt)->type == 1)
		(*str)++;
	(*str)++;
	while (iis(**str, &(*formatt)))
		(*str)++;
}
