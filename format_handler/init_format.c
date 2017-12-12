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

void	init_format(t_flags **formatt)
{
	int i;

	(*formatt) = (t_flags*)malloc(sizeof(t_flags));
	i = -1;
	while (++i < 5)
		(*formatt)->flags[i] = 0;
	(*formatt)->width_star = 0;
	(*formatt)->width_len = 0;
	(*formatt)->precision_star = 0;
	(*formatt)->precision_len = 0;
	(*formatt)->type = 0;
	(*formatt)->spec_flag = -1;
	(*formatt)->error = 0;
}
