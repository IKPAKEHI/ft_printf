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

static void		in0(char **tmp, const char **str, t_flags **formatt)
{
	(*tmp) = (char*)(*str);
	while (*(*str) && *(*str) != '%')
		(*str)++;
	type_error(ft_strsub((*tmp), 0, 1), &(*formatt));
	(*formatt)->error = 1;
	if (*(*tmp))
		(*tmp)++;
	while (*(*tmp) && *(*tmp) != '%')
		ft_putchar(*(*tmp)++);
}

t_flags			*ft_format(const char **str, va_list *list)
{
	t_flags	*formatt;
	char	*tmp;
	char	*types;

	types = "sSpdDioOuUxXcC% ";
	tmp = (char*)(*str) - 1;
	init_format(&formatt);
	if (!formatt)
		return (0);
	while (**str && (**str == '-' || **str == '+' || **str == ' ' ||
	**str == '#' || **str == '0'))
		check_flags(*(*str)++, &formatt);
	if ((**str >= '0' && **str <= '9') || **str == '*')
		check_width(&(*str), &formatt, &list);
	if (**str == '.')
		check_precision(&(*str), &formatt, &list);
	while (**str == 'h' || **str == 'l' || **str == 'j' || **str == 'z')
		check_type(&(*str), &formatt);
	while (*types)
		if (*(*str) == *types++)
			break ;
	if (*types == 0)
		in0(&tmp, &(*str), &formatt);
	return (formatt);
}
