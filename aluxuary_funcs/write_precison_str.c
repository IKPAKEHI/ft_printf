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

void	write_precison_str(char **str, t_flags **mody, int str_len)
{
	str_len++;
	if ((*mody)->precision_len == 0 && (*mody)->spec_flag != 1)
		return ;
	while ((int)ft_strlen(*str) != (*mody)->precision_len)
	{
		(*str)[ft_strlen(*str) - 1] = '\0';
	}
}
