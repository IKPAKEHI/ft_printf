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

#include "ft_printf.h"

static void		ft_init_funcs(void)
{
	g_types = "sSpdDioOuUxXcC% ";
	g_ret = 0;
	g_str = (char*)malloc(sizeof(char) * 32);
	g_i = 0;
	g_f[0] = type_s;
	g_f[1] = type_su;
	g_f[2] = type_p;
	g_f[3] = type_d;
	g_f[4] = type_du;
	g_f[5] = type_i;
	g_f[6] = type_o;
	g_f[7] = type_ou;
	g_f[8] = type_u;
	g_f[9] = type_uuu;
	g_f[10] = type_x;
	g_f[11] = type_xu;
	g_f[12] = type_c;
	g_f[13] = type_cu;
	g_f[14] = type_interest;
	g_f[15] = 0;
}

static int		ft_check_gstr(const char **format)
{
	if (g_i % 31 == 0)
		if (!(ft_realoc_str(&g_str, 32)))
			return (0);
	g_str[g_i++] = **format;
	(*format)++;
	return (1);
}

static void		in1(const char **f, int *i, va_list *l, t_flags **m)
{
	while (g_types[++(*i)])
		if (g_types[(*i)] == *(*f) && g_types[(*i)])
			g_f[(*i)](l, &(*m));
}

static int		in0(const char **f, int *i, va_list *l, t_flags **m)
{
	while (*(*f) && ((*i) = -1))
	{
		g_str[g_i] = 0;
		if (*(*f) == '%' && ((*f) += 1))
		{
			if (*(*f) == '\0')
				continue ;
			if (!((*m) = ft_format(&(*f), l)))
				return (1);
			if (*(*f) == 0 || (*m)->error == 1)
			{
				free((*m));
				continue ;
			}
			if (*(*f) != 'S')
				ft_putgstr();
			in1(&(*f), &(*i), l, &(*m));
			free((*m));
			(*f)++;
			continue;
		}
		if (!(ft_check_gstr(&(*f))))
			return (0);
	}
	return (2);
}

int				ft_printf(const char *format, ...)
{
	int		i;
	va_list	list;
	t_flags	*mody;
	int		err;

	ft_init_funcs();
	va_start(list, format);
	err = in0(&format, &i, &list, &mody);
	if (err == 1)
	{
		free(g_str);
		free(mody);
		return (-1);
	}
	else if (err == 0)
	{
		free(g_str);
		return (-1);
	}
	g_str[g_i] = 0;
	ft_putstr(g_str);
	free(g_str);
	va_end(list);
	return (g_ret);
}
