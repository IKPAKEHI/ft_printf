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

static void		in0(t_flags **mody, int *i, wchar_t **tmp, char *filler)
{
	ft_putgstr();
	if ((*mody)->flags[4] == 1 && (*mody)->flags[0] != 1)
		(*filler) = '0';
	if ((*mody)->precision_len == 0 && (*mody)->spec_flag == 0)
		(*tmp)[0] = 0;
	(*i) = 0;
	if ((*mody)->precision_len > 0)
		while ((ft_wstrlen((*tmp))) > (*mody)->precision_len)
			(*tmp)[(ft_wcharlen((*tmp)) - 1)] = 0;
	(*mody)->width_len -= (ft_wstrlen((*tmp)));
	if ((*mody)->width_len > 0 && (*mody)->flags[0] != 1)
		while ((*mody)->width_len--)
			ft_putchar((*filler));
	(*i) = 0;
	while ((*tmp)[(*i)] != 0)
		ft_putwchar((*tmp)[(*i)++]);
	if ((*mody)->width_len > 0 && (*mody)->flags[0] == 1)
		while ((*mody)->width_len--)
			ft_putchar((*filler));
	free((*tmp));
}

void			type_su(va_list *list, t_flags **mody)
{
	wchar_t	*tmp;
	int		i;
	char	filler;

	filler = ' ';
	if (!list || !mody || !(*mody))
		return ;
	tmp = ft_duplic_wchr(va_arg(*list, wchar_t*));
	if (tmp == 0)
	{
		ft_putgstr();
		ft_putstr("(null)");
		return ;
	}
	check_err_su(tmp);
	if (g_err == 1)
	{
		free(tmp);
		return ;
	}
	in0(&(*mody), &i, &tmp, &filler);
}
