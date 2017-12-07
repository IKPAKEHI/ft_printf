//проверить строки с точностью <= 0
//проверить строки с флагом 0
//%lc должно вроде как работать как %C

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#include <locale.h>

int g_ret;
int g_err;
char *g_str;
int g_i;

typedef struct	s_flags
{
	int		flags[5];
	int		width_star;
	int		width_len;
	int		precision_star;
	int		precision_len;
	int		type;
	int		spec_flag;
	int		error;
}				t_flags;


void		ft_putnbr(int n);
void		ft_putchar(char c);
void		ft_putstr(char const *str);
char		*ft_itoa_base(long long int value, int base);
char		*ft_itoa_base_u(unsigned long int value, int base, char later);
void		ft_putnbr_u(unsigned int n);
t_flags		*ft_format(char **str, va_list *list);
int			num_len(int n);
void		ft_write_spaces(char **str, int i, int alignment);
void		ft_write_zeros(char **str, int i, int plus, int minus);
size_t		ft_strlen(const char *s);
void		ft_write_num(char **res, char *num, int alignment, int plus);
void		write_precison(char **str, int i, int num_len, int alig);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		ft_make_0x(char **str, char c);
void		write_precison_str(char **str, t_flags **mody, int str_len);
void		ft_putwstr(wchar_t const *str);
void		ft_putwchar(wchar_t c);
void		ft_make_0x_p(char **str, char c);
char		*ft_strdup(const char *s1);
char		*ft_strsub(char const *s, unsigned int start, size_t len);
wchar_t		*ft_duplic_wchr(wchar_t *str);
int			ft_wstrlen(wchar_t *str);
int			ft_wcharlen(wchar_t *str);
char		*ft_strjoin(char *s1, char *s2);


typedef void funcs(va_list *list, t_flags **mody);

void		type_s(va_list *list, t_flags **mody);
void		type_S(va_list *list, t_flags **mody);
void		type_p(va_list *list, t_flags **mody);
void		type_d(va_list *list, t_flags **mody);
void		type_D(va_list *list, t_flags **mody);
void		type_i(va_list *list, t_flags **mody);
void		type_o(va_list *list, t_flags **mody);
void		type_O(va_list *list, t_flags **mody);
void		type_u(va_list *list, t_flags **mody);
void		type_U(va_list *list, t_flags **mody);
void		type_x(va_list *list, t_flags **mody);
void		type_X(va_list *list, t_flags **mody);
void		type_c(va_list *list, t_flags **mody);
void		type_C(va_list *list, t_flags **mody);
void		type_interest(va_list *list, t_flags **mody);
int			ft_printf(char *format, ...);

static int		ft_realoc_str(char **str, int len)
{
	char	*tmp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if ((*str) == 0 || str == 0)
		return (0);
	if (!(tmp = (char*)malloc(sizeof(char) * (ft_strlen(*str) + 1))))
		return (0);
	while ((*str)[j])
		tmp[i++] = (*str)[j++];
	tmp[i] = 0;
	free((*str));
	if (!(*str = (char*)malloc(sizeof(char) *
		(ft_strlen(tmp) + len + 1))))
		return (0);
	i = 0;
	j = 0;
	while (tmp[j])
		(*str)[i++] = tmp[j++];
	(*str)[i] = 0;
	free(tmp);
	return (1);
}

void ft_putgstr(void)
{
	ft_putstr(g_str);
	free(g_str);
	g_str = (char*)malloc(sizeof(char) * 32);
	g_i = 0;
}

int			ft_printf(char *format, ...)
{
	char *types = "sSpdDioOuUxXcC% ";
	funcs* f[16];
	va_list list;
	int i;
	t_flags *mody;


	g_ret = 0;
	f[0] = type_s;
	f[1] = type_S;
	f[2] = type_p;
	f[3] = type_d;
	f[4] = type_D;
	f[5] = type_i;
	f[6] = type_o;
	f[7] = type_O;
	f[8] = type_u;
	f[9] = type_U;
	f[10] = type_x;
	f[11] = type_X;
	f[12] = type_c;
	f[13] = type_C;
	f[14] = type_interest;
	f[15] = 0;

	va_start(list, format);

	g_str = (char*)malloc(sizeof(char) * 32);
	g_i = 0;
	while (*format)
	{
		i = 0;
		g_str[g_i] = 0;
		if (*format == '%')
		{
			format++;
			if (*format == '\0')
				continue ;
			mody = ft_format(&format, &list);
			if (*format == 0 || mody->error == 1)
			{
				free(mody);
				continue ;
			}
			if (*format != 'S')
				ft_putgstr();
			while (types[i])
			{
				if (types[i] == *format && types[i])
					f[i](&list, &mody);
				i++;	
			}
			free(mody);
			format++;
			continue;
		}
		if (g_i % 31 == 0)
			ft_realoc_str(&g_str, 32);
		g_str[g_i++] = *format++;
	}
	g_str[g_i] = 0;
	ft_putstr(g_str);
	free(g_str);
	va_end(list);
	return (g_ret);
}

////////////////////////////////////////////////////////////////////////////////////

void type_interest(va_list *list, t_flags **mody)
{
	char	*res;
	int		res_len;
	char	filler;

	filler = ' ';
	res_len = (*mody)->width_len == 0 ? 1 : (*mody)->width_len;
	res = (char*)malloc(sizeof(char) * res_len + 1);
	res[res_len] = 0;
	if ((*mody)->flags[0] == 1)
	{
		res[0] = '%';
		while (res_len != 1)
			res[--res_len] = filler;
		ft_putstr(res);
		return ;
	}
	filler = ((*mody)->flags[4] == 1) ? '0' : ' ';
	res[--res_len] = '%';
	while (res_len)
		res[--res_len] = filler;
	ft_putstr(res);
	free(res);
}


void type_s(va_list *list, t_flags **mody)
{
	char *tmp; 
	int res_len;
	char *res;
	if ((*mody)->type == 4)
	{
		type_S(list, &(*mody));
		return ;
	}
	tmp = ft_strdup(va_arg(*list, char*));
	if ((*mody)->precision_len == 0 && (*mody)->spec_flag == 0)
	{
		free(tmp);
		tmp = ft_strdup("");
	}
	if (tmp == 0)
	{
		ft_putstr("(null)");
		return ;
	}
	if ((*mody)->precision_len > (int)ft_strlen(tmp))
		(*mody)->precision_len = 0;
	if ((*mody)->flags[1] == 1)
		(*mody)->flags[1] = 0;
	if ((*mody)->flags[0] == 1) //если есть флаг - то флаг 0 игнорируестя
		(*mody)->flags[4] = 0;
	if ((*mody)->flags[4] == 1 && ((*mody)->precision_star > 0 || (*mody)->precision_len > 0))
		(*mody)->flags[4] = 0;
	if (tmp[0] == '\0')
		(*mody)->precision_len = 0;
	if ((*mody)->precision_len >= 0 && (*mody)->precision_len <  (int)ft_strlen(tmp))
			write_precison_str(&tmp, &(*mody), (int)ft_strlen(tmp));
	res_len = (*mody)->precision_len <= (*mody)->width_len ? (*mody)->width_len : (*mody)->precision_len;
	if ((tmp[0] == '-' || (*mody)->flags[1] == 1) && (*mody)->precision_len >= (int)ft_strlen(tmp))
	{
		if ((*mody)->width_len <= (*mody)->precision_len)
			res_len++;
		if ((*mody)->flags[1] != 1)
			(*mody)->precision_len++;
	}
	if (res_len < (int)ft_strlen(tmp))
	{
		res_len = ft_strlen(tmp);
		if ((*mody)->flags[1] == 1)
			res_len++;
	}
	res = (char*)malloc(sizeof(char) * (res_len + 1));
	res[res_len] = 0;
	res_len--;
	while (res_len != -1)
		res[res_len--] = ' ';
	if ((*mody)->flags[4] == 0)
		ft_write_spaces(&res,(*mody)->width_len, (*mody)->flags[0]);
	if ((*mody)->flags[4] == 1)
		ft_write_zeros(&res,(*mody)->width_len, (*mody)->flags[0], 0);

	ft_write_num(&res, tmp, (*mody)->flags[0], (*mody)->flags[1]);
	ft_putstr(res);
	free(res);
	free(tmp);
}

void 	check_err_S(wchar_t *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(str[i] > 2097152)
			g_err = 1;
		i++;
	}
}

// int main(int argc, char const *argv[])
// {
// 	ft_printf("%S", L"asdas##@#@#@()()()()(das");
// 	return 0;
// }

void type_S(va_list *list, t_flags **mody)
{	
	wchar_t *tmp;
	int i;
	int str_len;
	char filler;

	filler = ' ';
	tmp = ft_duplic_wchr(va_arg(*list, wchar_t*));
	if (tmp == 0)
	{
		ft_putgstr();
		ft_putstr("(null)");
		return ;
	}
	check_err_S(tmp);
	if (g_err == 1)
	{
		free(tmp);
		return ;
	}
	ft_putgstr();
	if ((*mody)->flags[4] == 1 && (*mody)->flags[0] != 1)
		filler = '0';
	if ((*mody)->precision_len == 0 && (*mody)->spec_flag == 0)
		tmp[0] = 0; 
	i = 0;
	if ((*mody)->precision_len > 0)
		while ((ft_wstrlen(tmp)) > (*mody)->precision_len)
			tmp[(ft_wcharlen(tmp) - 1)] = 0;
	(*mody)->width_len -= (ft_wstrlen(tmp));
	if ((*mody)->width_len > 0 && (*mody)->flags[0] != 1)
		while((*mody)->width_len--)
			ft_putchar(filler);
	i = 0;
	while(tmp[i])
		ft_putwchar(tmp[i++]);
	if ((*mody)->width_len > 0 && (*mody)->flags[0] == 1)
		while((*mody)->width_len--)
			ft_putchar(filler);	
	free(tmp);

}

void ft_realochex(char **str, char c,char **to_free)
{
	char *tmp;
	int i;
	int j;

	i = 0;
	j = 0;
	tmp = (char*)malloc(sizeof(char) * ft_strlen(*str));
	while ((*str)[i])
		tmp[j++] = (*str)[i++];
	tmp[j] = 0;
	free(*to_free);
	(*str) = (char*)malloc(sizeof(char) * ft_strlen(tmp) + 4);
	i = 2;
	j = 0;
	(*str)[0] = '0';
	(*str)[1] = c;
	while (tmp[j])
		(*str)[i++] = tmp[j++];
	(*str)[i] = 0;
	free(tmp);
}


void type_p(va_list *list, t_flags **mody)
{
	char *num;
	int res_len;
	char *res;
	char *to_free;

	if ((*mody)->flags[1] == 1)
		(*mody)->flags[1] = 0;
	num = ft_itoa_base(va_arg(*list, long long int), 16);
	to_free = num;
	(*mody)->precision_len+=2;
	if (num[0] == '0' && num[1] == '\0' && (*mody)->spec_flag == 0)
		num++;
	ft_realochex(&num, 'x', &to_free);
	to_free = num;
	if (num[0] == '-')
	{
		(*mody)->flags[1] = 0;
		(*mody)->flags[2] = 0;
	}
	if ((*mody)->flags[0] == 1)
		(*mody)->flags[4] = 0;
	if ((*mody)->flags[4] == 1 && ((*mody)->precision_star > 0 || (*mody)->precision_len > 2))
		(*mody)->flags[4] = 0;
	res_len = (*mody)->precision_len <= (*mody)->width_len ? (*mody)->width_len : (*mody)->precision_len;
	if ((num[0] == '-' || (*mody)->flags[1] == 1) && (*mody)->precision_len >= (int)ft_strlen(num))
	{
		if ((*mody)->width_len <= (*mody)->precision_len)
			res_len++;
		if ((*mody)->flags[1] != 1)
			(*mody)->precision_len++;
	}
	if (res_len < (int)ft_strlen(num))
	{
		res_len = ft_strlen(num);
		if ((*mody)->flags[1] == 1)
			res_len++;
	}
	res = (char*)malloc(sizeof(char) * (res_len + 1));
	res[res_len] = 0;
	res_len--;
	while (res_len != -1)
		res[res_len--] = ' ';
	(*mody)->precision_len -= ft_strlen(num);
	(*mody)->width_len -= ft_strlen(num);
	if ((*mody)->precision_len > 0 && (*mody)->width_len > 0 && (*mody)->width_len > (*mody)->precision_len)
		(*mody)->width_len -= (*mody)->precision_len;
	if ((*mody)->flags[4] == 1)
		ft_write_zeros(&res,(*mody)->width_len, (*mody)->flags[1], 1);
	if ((*mody)->flags[4] == 0)
		ft_write_spaces(&res,(*mody)->width_len, (*mody)->flags[0]);
	ft_write_num(&res, num, (*mody)->flags[0], (*mody)->flags[1]);
	if ((*mody)->precision_len > 0)
		write_precison(&res, (*mody)->precision_len, ft_strlen(num), (*mody)->flags[0]);
	ft_make_0x_p(&res, 'x');
	ft_putstr(res);
	free(res);
	free(to_free);
}

void type_d(va_list *list, t_flags **mody)
{
	long long int a;
	char *num;
	int res_len;
	char *res;
	char *to_free;
	if ((*mody)->width_len < 0)
	{
		(*mody)->width_len *= -1;
		(*mody)->flags[0] = 1;
	}
	if ((*mody)->type == 1)
		a = (char)va_arg(*list, long int);
	else if ((*mody)->type == 2)
		a = (short)va_arg(*list, long int);
	else if ((*mody)->type == 3)
		a = (long long int)va_arg(*list, long long int);
	else if ((*mody)->type == 4)
		a = (long int)va_arg(*list, long int);
	else if ((*mody)->type == 5)
		a = (long long int)va_arg(*list, long long int);
	else if ((*mody)->type == 6)
		a = (size_t)va_arg(*list, size_t);
	else
		a = (int)va_arg(*list, int);
	num = ft_itoa_base(a, 10);
	to_free = num;
	if ((*mody)->flags[1] == 0 && (*mody)->flags[2] == 1 && num[0] != '-')
	{
		ft_putchar(' ');
		if ((*mody)->width_len > 0)
		(*mody)->width_len--;
		(*mody)->flags[2]= 0;
	}
	if (num[0] == '0' && num[1] == '\0' && (*mody)->spec_flag == 0)
		num++;
	if (num[0] == '-')
	{
		(*mody)->flags[1] = 0;
		(*mody)->flags[2] = 0;
	}
	if ((*mody)->flags[0] == 1)
		(*mody)->flags[4] = 0;
	if ((*mody)->flags[4] == 1 && ((*mody)->precision_star > 0 || (*mody)->precision_len > 0))
		(*mody)->flags[4] = 0;
	res_len = (*mody)->precision_len <= (*mody)->width_len ? (*mody)->width_len : (*mody)->precision_len;
	if ((num[0] == '-' || (*mody)->flags[1] == 1) && (*mody)->precision_len >= (int)ft_strlen(num))
	{
		if ((*mody)->width_len <= (*mody)->precision_len)
			res_len++;
		if ((*mody)->flags[1] != 1)
			(*mody)->precision_len++;
	}
	if (res_len < (int)ft_strlen(num))
	{
		res_len = ft_strlen(num);
		if ((*mody)->flags[1] == 1 || (*mody)->flags[2] == 1)
			res_len++;
	}
	res = (char*)malloc(sizeof(char) * (res_len + 1));
	res[res_len] = 0;
	res_len--;
	while (res_len != -1)
		res[res_len--] = ' ';
	(*mody)->precision_len -= ft_strlen(num);
	(*mody)->width_len -= ft_strlen(num);
	if ((*mody)->precision_len > 0 && (*mody)->width_len > 0 && (*mody)->width_len > (*mody)->precision_len)
		(*mody)->width_len -= (*mody)->precision_len;
	if ((*mody)->flags[4] == 1)
		ft_write_zeros(&res,(*mody)->width_len, (*mody)->flags[1], a);
	if ((*mody)->flags[4] == 0)
		ft_write_spaces(&res,(*mody)->width_len, (*mody)->flags[0]);

	ft_write_num(&res, num, (*mody)->flags[0], (*mody)->flags[1]);
	if ((*mody)->precision_len > 0)
		write_precison(&res, (*mody)->precision_len, ft_strlen(num), (*mody)->flags[0]);
	ft_putstr(res);
	free(res);
	free(to_free);
}

void type_D(va_list *list, t_flags **mody)
{
	long long int a;

	
	if ((*mody)->type == 1)
		a = (unsigned short)va_arg(*list, unsigned long int);
	else if ((*mody)->type == 2)
		a = (unsigned short)va_arg(*list, unsigned long int);
	else if ((*mody)->type == 3)
		a = (unsigned long int)va_arg(*list, unsigned long int);
	else if ((*mody)->type == 4)
		a = (unsigned long int)va_arg(*list, unsigned long int);
	else if ((*mody)->type == 5)
		a = (unsigned long int)va_arg(*list, unsigned long int);
	else if ((*mody)->type == 6)
		a = (size_t)va_arg(*list, size_t);
	else
		a = (long int)va_arg(*list, long int);
	char *num;
	int res_len;
	char *res;
	char *to_free;
	num = ft_itoa_base(a, 10);
	to_free = num;
	if ((*mody)->flags[1] == 0 && (*mody)->flags[2] == 1 && num[0] != '-')
	{
		ft_putchar(' ');
		if ((*mody)->width_len > 0)
		(*mody)->width_len--;
		(*mody)->flags[2]= 0;
	}
	if (num[0] == '0' && num[1] == '\0' && (*mody)->spec_flag == 0)
		num++;
	if (num[0] == '-')
	{
		(*mody)->flags[1] = 0;
		(*mody)->flags[2] = 0;
	}
	if ((*mody)->flags[0] == 1)
		(*mody)->flags[4] = 0;
	if ((*mody)->flags[4] == 1 && ((*mody)->precision_star > 0 || (*mody)->precision_len > 0))
		(*mody)->flags[4] = 0;
	res_len = (*mody)->precision_len <= (*mody)->width_len ? (*mody)->width_len : (*mody)->precision_len;
	if ((num[0] == '-' || (*mody)->flags[1] == 1) && (*mody)->precision_len >= (int)ft_strlen(num))
	{
		if ((*mody)->width_len <= (*mody)->precision_len)
			res_len++;
		if ((*mody)->flags[1] != 1)
			(*mody)->precision_len++;
	}
	if (res_len < (int)ft_strlen(num))
	{
		res_len = ft_strlen(num);
		if ((*mody)->flags[1] == 1 || (*mody)->flags[2] == 1)
			res_len++;
	}
	res = (char*)malloc(sizeof(char) * (res_len + 1));
	res[res_len] = 0;
	res_len--;
	while (res_len != -1)
		res[res_len--] = ' ';
	(*mody)->precision_len -= ft_strlen(num);
	(*mody)->width_len -= ft_strlen(num);
	if ((*mody)->precision_len > 0 && (*mody)->width_len > 0 && (*mody)->width_len > (*mody)->precision_len)
		(*mody)->width_len -= (*mody)->precision_len;
	if ((*mody)->flags[4] == 1)
		ft_write_zeros(&res,(*mody)->width_len, (*mody)->flags[1], a);
	if ((*mody)->flags[4] == 0)
		ft_write_spaces(&res,(*mody)->width_len, (*mody)->flags[0]);
	ft_write_num(&res, num, (*mody)->flags[0], (*mody)->flags[1]);
	if ((*mody)->precision_len > 0)
		write_precison(&res, (*mody)->precision_len, ft_strlen(num), (*mody)->flags[0]);
	ft_putstr(res);
	free(res);
	free(to_free);
}

void type_i(va_list *list, t_flags **mody)
{
	long long int a;

	if ((*mody)->type == 1)
		a = (char)va_arg(*list, long int);
	else if ((*mody)->type == 2)
		a = (short)va_arg(*list, long int);
	else if ((*mody)->type == 3)
		a = (long long int)va_arg(*list, long long int);
	else if ((*mody)->type == 4)
		a = (long int)va_arg(*list, long int);
	else if ((*mody)->type == 5)
		a = (long long int)va_arg(*list, long long int);
	else if ((*mody)->type == 6)
		a = (size_t)va_arg(*list, size_t);
	else
		a = (int)va_arg(*list, int);
	char *num;
	int res_len;
	char *res;
	char *to_free;
	num = ft_itoa_base(a, 10);
	to_free = num;
	if ((*mody)->flags[1] == 0 && (*mody)->flags[2] == 1 && num[0] != '-')
	{
		ft_putchar(' ');
		if ((*mody)->width_len > 0)
		(*mody)->width_len--;
		(*mody)->flags[2]= 0;
	}
	if (num[0] == '0' && num[1] == '\0' && (*mody)->spec_flag == 0)
		num++;
	if (num[0] == '-')
	{
		(*mody)->flags[1] = 0;
		(*mody)->flags[2] = 0;
	}
	if ((*mody)->flags[0] == 1)
		(*mody)->flags[4] = 0;
	if ((*mody)->flags[4] == 1 && ((*mody)->precision_star > 0 || (*mody)->precision_len > 0))
		(*mody)->flags[4] = 0;
	res_len = (*mody)->precision_len <= (*mody)->width_len ? (*mody)->width_len : (*mody)->precision_len;
	if ((num[0] == '-' || (*mody)->flags[1] == 1) && (*mody)->precision_len >= (int)ft_strlen(num))
	{
		if ((*mody)->width_len <= (*mody)->precision_len)
			res_len++;
		if ((*mody)->flags[1] != 1)
			(*mody)->precision_len++;
	}
	if (res_len < (int)ft_strlen(num))
	{
		res_len = ft_strlen(num);
		if ((*mody)->flags[1] == 1 || (*mody)->flags[2] == 1)
			res_len++;
	}
	res = (char*)malloc(sizeof(char) * (res_len + 1));
	res[res_len] = 0;
	res_len--;
	while (res_len != -1)
		res[res_len--] = ' ';
	(*mody)->precision_len -= ft_strlen(num);
	(*mody)->width_len -= ft_strlen(num);
	if ((*mody)->precision_len > 0 && (*mody)->width_len > 0 && (*mody)->width_len > (*mody)->precision_len)
		(*mody)->width_len -= (*mody)->precision_len;
	if ((*mody)->flags[4] == 1)
		ft_write_zeros(&res,(*mody)->width_len, (*mody)->flags[1], a);
	if ((*mody)->flags[4] == 0)
		ft_write_spaces(&res,(*mody)->width_len, (*mody)->flags[0]);
	ft_write_num(&res, num, (*mody)->flags[0], (*mody)->flags[1]);
	if ((*mody)->precision_len > 0)
		write_precison(&res, (*mody)->precision_len, ft_strlen(num), (*mody)->flags[0]);
	ft_putstr(res);
	free(res);
	free(to_free);
}

void ft_realooctal(char **str, char c,char **to_free)
{
	char *tmp;
	int i;
	int j;

	i = 0;
	j = 0;
	tmp = (char*)malloc(sizeof(char) * ft_strlen(*str));
	while ((*str)[i])
		tmp[j++] = (*str)[i++];
	tmp[j] = 0;
	free(*to_free);
	(*str) = (char*)malloc(sizeof(char) * ft_strlen(tmp) + 2);
	i = 1;
	j = 0;
	(*str)[0] = c;
	while (tmp[j])
		(*str)[i++] = tmp[j++];
	(*str)[i] = 0;
	free(tmp);
}

void type_o(va_list *list, t_flags **mody)
{
	long int a;
	char *num;
	int res_len;
	char *res;
	char *to_free;

	if ((*mody)->type == 1)
		a = (unsigned char)va_arg(*list, long int);
	else if ((*mody)->type == 2)
		a = (unsigned short)va_arg(*list, long int);
	else if ((*mody)->type == 3)
		a = (unsigned long long)va_arg(*list, unsigned long long);
	else if ((*mody)->type == 4)
		a = (unsigned long)va_arg(*list, unsigned long);
	else if ((*mody)->type == 5)
		a = va_arg(*list, long int);
	else if ((*mody)->type == 6)
		a = (size_t)va_arg(*list, size_t);
	else
		a = (unsigned int)va_arg(*list, long int);
	
	num =  ft_itoa_base_u(a, 8, 'a');
	to_free = num;

	if ((*mody)->flags[1] == 1)
		(*mody)->flags[1] = 0;

	if (num[0] == '0' && num[1] == '\0' && (*mody)->spec_flag == 0 && (*mody)->flags[3] != 1)
		num++;
	if ((*mody)->flags[3] == 1 && num[0] != '0')
	{
		ft_realooctal(&num, '0', & to_free);
		to_free = num;
	}
	if (num[0] == '-')
	{
		(*mody)->flags[1] = 0;
		(*mody)->flags[2] = 0;
	}
	if ((*mody)->flags[0] == 1)
		(*mody)->flags[4] = 0;
	if ((*mody)->flags[4] == 1 && ((*mody)->precision_star > 0 || (*mody)->precision_len > 0))
		(*mody)->flags[4] = 0;
	res_len = (*mody)->precision_len <= (*mody)->width_len ? (*mody)->width_len : (*mody)->precision_len;
	if ((num[0] == '-' || (*mody)->flags[1] == 1) && (*mody)->precision_len >= (int)ft_strlen(num))
	{
		if ((*mody)->width_len <= (*mody)->precision_len)
			res_len++;
		if ((*mody)->flags[1] != 1)
			(*mody)->precision_len++;
	}
	if (res_len < (int)ft_strlen(num))
	{
		res_len = ft_strlen(num);
		if ((*mody)->flags[1] == 1)
			res_len++;
	}
	res = (char*)malloc(sizeof(char) * (res_len + 1));
	res[res_len] = 0;
	res_len--;
	while (res_len != -1)
		res[res_len--] = ' ';
	(*mody)->precision_len -= ft_strlen(num);
	(*mody)->width_len -= ft_strlen(num);
	if ((*mody)->precision_len > 0 && (*mody)->width_len > 0 && (*mody)->width_len > (*mody)->precision_len)
		(*mody)->width_len -= (*mody)->precision_len;
	if ((*mody)->flags[4] == 1)
		ft_write_zeros(&res,(*mody)->width_len, (*mody)->flags[1], a);
	if ((*mody)->flags[4] == 0)
		ft_write_spaces(&res,(*mody)->width_len, (*mody)->flags[0]);
	ft_write_num(&res, num, (*mody)->flags[0], (*mody)->flags[1]);
	if ((*mody)->precision_len > 0)
		write_precison(&res, (*mody)->precision_len, ft_strlen(num), (*mody)->flags[0]);
	ft_putstr(res);
	free(res);
	free(to_free);
}

void type_O(va_list *list, t_flags **mody)
{
	unsigned long int a;
	char *num;
	int res_len;
	char *res;
	char *to_free;

	if ((*mody)->type == 1)
		a = (unsigned short)va_arg(*list, unsigned long int);
	else if ((*mody)->type == 2)
		a = (unsigned short)va_arg(*list, unsigned long int);
	else if ((*mody)->type == 3)
		a = (unsigned long long)va_arg(*list, unsigned long long);
	else if ((*mody)->type == 4)
		a = (unsigned long)va_arg(*list, unsigned long);
	else if ((*mody)->type == 5)
		a = va_arg(*list, unsigned long int);
	else if ((*mody)->type == 6)
		a = (size_t)va_arg(*list, size_t);
	else
		a = (unsigned long int)va_arg(*list, unsigned long int);
	num =  ft_itoa_base_u(a, 8, 'a');
	to_free = num;
	if ((*mody)->flags[1] == 1)
		(*mody)->flags[1] = 0;
	if (num[1] != '\0')
	while (*num == '0')
		num++;
	if (num[0] == '0' && num[1] == '\0' && (*mody)->spec_flag == 0 && (*mody)->flags[3] != 1)
		num++;
	if ((*mody)->flags[3] == 1 && num[0] != '0')
	{
		ft_realooctal(&num, '0', & to_free);
		to_free = num;
	}
	if (num[0] == '-')
	{
		(*mody)->flags[1] = 0;
		(*mody)->flags[2] = 0;
	}
	if ((*mody)->flags[0] == 1)
		(*mody)->flags[4] = 0;
	if ((*mody)->flags[4] == 1 && ((*mody)->precision_star > 0 || (*mody)->precision_len > 0))
		(*mody)->flags[4] = 0;
	res_len = (*mody)->precision_len <= (*mody)->width_len ? (*mody)->width_len : (*mody)->precision_len;
	if ((num[0] == '-' || (*mody)->flags[1] == 1) && (*mody)->precision_len >= (int)ft_strlen(num))
	{
		if ((*mody)->width_len <= (*mody)->precision_len)
			res_len++;
		if ((*mody)->flags[1] != 1)
			(*mody)->precision_len++;
	}
	if (res_len < (int)ft_strlen(num))
	{
		res_len = ft_strlen(num);
		if ((*mody)->flags[1] == 1)
			res_len++;
	}
	res = (char*)malloc(sizeof(char) * (res_len + 1));
	res[res_len] = 0;
	res_len--;
	while (res_len != -1)
		res[res_len--] = ' ';
	(*mody)->precision_len -= ft_strlen(num);
	(*mody)->width_len -= ft_strlen(num);
	if ((*mody)->precision_len > 0 && (*mody)->width_len > 0 && (*mody)->width_len > (*mody)->precision_len)
		(*mody)->width_len -= (*mody)->precision_len;
	if ((*mody)->flags[4] == 1)
		ft_write_zeros(&res,(*mody)->width_len, (*mody)->flags[1], a);
	if ((*mody)->flags[4] == 0)
		ft_write_spaces(&res,(*mody)->width_len, (*mody)->flags[0]);
	ft_write_num(&res, num, (*mody)->flags[0], (*mody)->flags[1]);
	if ((*mody)->precision_len > 0)
		write_precison(&res, (*mody)->precision_len, ft_strlen(num), (*mody)->flags[0]);
	ft_putstr(res);
	free(res);
	free(to_free);
}


void type_u(va_list *list, t_flags **mody)
{
	unsigned long long int a;
	char *num;
	int res_len;
	char *res;
	char *to_free;

	if ((*mody)->type == 1)
		a = (unsigned char)va_arg(*list, unsigned long long int);
	else if ((*mody)->type == 2)
		a = (unsigned short)va_arg(*list, unsigned long long int);
	else if ((*mody)->type == 3)
		a = (unsigned long long int)va_arg(*list, unsigned long long int);
	else if ((*mody)->type == 4)
		a = (unsigned long int)va_arg(*list, unsigned long long int);
	else if ((*mody)->type == 5)
		a = (unsigned long long int)va_arg(*list, unsigned long long int);
	else if ((*mody)->type == 6)
		a = (size_t)va_arg(*list, unsigned long long int);
	else
		a = (unsigned int)va_arg(*list, unsigned int);
	num = ft_itoa_base_u(a, 10, 'a');
	to_free = num;
	(*mody)->flags[1] = 0;
	if (num[0] == '0' && num[1] == '\0' && (*mody)->spec_flag == 0)
		num++;
	if (num[0] == '-')
		(*mody)->flags[2] = 0;
	if ((*mody)->flags[0] == 1)
		(*mody)->flags[4] = 0;
	if ((*mody)->flags[4] == 1 && ((*mody)->precision_star > 0 || (*mody)->precision_len > 0))
		(*mody)->flags[4] = 0;

	res_len = (*mody)->precision_len <= (*mody)->width_len ? (*mody)->width_len : (*mody)->precision_len;
	if ((num[0] == '-' || (*mody)->flags[1] == 1) && (*mody)->precision_len >= (int)ft_strlen(num))
	{
		if ((*mody)->width_len <= (*mody)->precision_len)
			res_len++;
		if ((*mody)->flags[1] != 1)
			(*mody)->precision_len++;
	}
	if (res_len < (int)ft_strlen(num))
	{
		res_len = ft_strlen(num);
		if ((*mody)->flags[1] == 1)
			res_len++;
	}
	res = (char*)malloc(sizeof(char) * (res_len + 1));
	res[res_len] = 0;
	res_len--;
	while (res_len != -1)
		res[res_len--] = ' ';
	(*mody)->precision_len -= ft_strlen(num);
	(*mody)->width_len -= ft_strlen(num);
	if ((*mody)->precision_len > 0 && (*mody)->width_len > 0 && (*mody)->width_len > (*mody)->precision_len)
		(*mody)->width_len -= (*mody)->precision_len;
	if ((*mody)->flags[4] == 1)
		ft_write_zeros(&res,(*mody)->width_len, (*mody)->flags[1], 1);
	if ((*mody)->flags[4] == 0)
		ft_write_spaces(&res,(*mody)->width_len, (*mody)->flags[0]);
	ft_write_num(&res, num, (*mody)->flags[0], (*mody)->flags[1]);
	if ((*mody)->precision_len > 0)
		write_precison(&res, (*mody)->precision_len, ft_strlen(num), (*mody)->flags[0]);
	ft_putstr(res);
	free(to_free);
	free(res);
}

void type_U(va_list *list, t_flags **mody)
{
	unsigned long long int a;
	char *num;
	int res_len;
	char *res;
	char *to_free;

	if ((*mody)->type == 1)
		a = (unsigned short)va_arg(*list, unsigned long long int);
	else if ((*mody)->type == 2)
		a = (unsigned long)va_arg(*list, unsigned long long int);
	else if ((*mody)->type == 3)
		a = (unsigned long long int)va_arg(*list, unsigned long long int);
	else if ((*mody)->type == 4)
		a = (unsigned long int)va_arg(*list, unsigned long long int);
	else if ((*mody)->type == 5)
		a = (unsigned long long int)va_arg(*list, unsigned long long int);
	else if ((*mody)->type == 6)
		a = (size_t)va_arg(*list, unsigned long long int);
	else
		a = (unsigned long)va_arg(*list, unsigned long);
	num = ft_itoa_base_u(a, 10, 'a');
	to_free = num;
	(*mody)->flags[1] = 0;
	if (num[0] == '0' && num[1] == '\0' && (*mody)->spec_flag == 0)
		num++;
	if (num[0] == '-')
		(*mody)->flags[2] = 0;
	if ((*mody)->flags[0] == 1)
		(*mody)->flags[4] = 0;
	if ((*mody)->flags[4] == 1 && ((*mody)->precision_star > 0 || (*mody)->precision_len > 0))
		(*mody)->flags[4] = 0;
	res_len = (*mody)->precision_len <= (*mody)->width_len ? (*mody)->width_len : (*mody)->precision_len;
	if ((num[0] == '-' || (*mody)->flags[1] == 1) && (*mody)->precision_len >= (int)ft_strlen(num))
	{
		if ((*mody)->width_len <= (*mody)->precision_len)
			res_len++;
		if ((*mody)->flags[1] != 1)
			(*mody)->precision_len++;
	}
	if (res_len < (int)ft_strlen(num))
	{
		res_len = ft_strlen(num);
		if ((*mody)->flags[1] == 1)
			res_len++;
	}
	res = (char*)malloc(sizeof(char) * (res_len + 1));
	res[res_len] = 0;
	res_len--;
	while (res_len != -1)
		res[res_len--] = ' ';
	(*mody)->precision_len -= ft_strlen(num);
	(*mody)->width_len -= ft_strlen(num);
	if ((*mody)->precision_len > 0 && (*mody)->width_len > 0 && (*mody)->width_len > (*mody)->precision_len)
		(*mody)->width_len -= (*mody)->precision_len;
	if ((*mody)->flags[4] == 1)
		ft_write_zeros(&res,(*mody)->width_len, (*mody)->flags[1], 1);
	if ((*mody)->flags[4] == 0)
		ft_write_spaces(&res,(*mody)->width_len, (*mody)->flags[0]);
	ft_write_num(&res, num, (*mody)->flags[0], (*mody)->flags[1]);
	if ((*mody)->precision_len > 0)
		write_precison(&res, (*mody)->precision_len, ft_strlen(num), (*mody)->flags[0]);
	ft_putstr(res);
	free(res);
	free(to_free);
}


void type_x(va_list *list, t_flags **mody)
{
	long int a;
	char *num;
	int res_len;
	char *res;
	char *to_free;
		
	if ((*mody)->type == 1)
		a = (unsigned char)va_arg(*list, long int);
	else if ((*mody)->type == 2)
		a = (unsigned short)va_arg(*list, long int);
	else if ((*mody)->type == 3)
		a = (unsigned long long)va_arg(*list, unsigned long long);
	else if ((*mody)->type == 4)
		a = (unsigned long)va_arg(*list, unsigned long);
	else if ((*mody)->type == 5)
		a = va_arg(*list, long int);
	else if ((*mody)->type == 6)
		a = (size_t)va_arg(*list, size_t);
	else
		a = (unsigned int)va_arg(*list, long int);
	num =  ft_itoa_base_u(a, 16, 'a');
	to_free = num;
	if (num[0] == '0' && num[1] == '\0' && (*mody)->spec_flag == 0)
		num++;
	if ((*mody)->flags[1] == 1)
		(*mody)->flags[1] = 0;

	if ((*mody)->flags[3] == 1 && a != 0)
	{
		ft_realochex(&num, 'x', &to_free);
		(*mody)->precision_len += 2;
		to_free = num;
	}
	if (num[0] == '-')
	{
		(*mody)->flags[1] = 0;
		(*mody)->flags[2] = 0;
	}
	if ((*mody)->flags[0] == 1)
		(*mody)->flags[4] = 0;
	if ((*mody)->flags[4] == 1 && ((*mody)->precision_len > 2))
		(*mody)->flags[4] = 0;
	res_len = (*mody)->precision_len <= (*mody)->width_len ? (*mody)->width_len : (*mody)->precision_len;
	if ((num[0] == '-' || (*mody)->flags[1] == 1) && (*mody)->precision_len >= (int)ft_strlen(num))
	{
		if ((*mody)->width_len <= (*mody)->precision_len)
			res_len++;
		if ((*mody)->flags[1] != 1)
			(*mody)->precision_len++;
	}
	if (res_len < (int)ft_strlen(num))
	{
		res_len = ft_strlen(num);
		if ((*mody)->flags[1] == 1)
			res_len++;
	}
	res = (char*)malloc(sizeof(char) * (res_len + 1));
	res[res_len] = 0;
	res_len--;
	while (res_len != -1)
		res[res_len--] = ' ';
	(*mody)->precision_len -= ft_strlen(num);
	(*mody)->width_len -= ft_strlen(num);
	if ((*mody)->precision_len > 0 && (*mody)->width_len > 0 && (*mody)->width_len > (*mody)->precision_len)
		(*mody)->width_len -= (*mody)->precision_len;
	if ((*mody)->flags[4] == 1)
		ft_write_zeros(&res,(*mody)->width_len, (*mody)->flags[1], a);
	if ((*mody)->flags[4] == 0)
		ft_write_spaces(&res,(*mody)->width_len, (*mody)->flags[0]);
	ft_write_num(&res, num, (*mody)->flags[0], (*mody)->flags[1]);
	if ((*mody)->precision_len > 0)
		write_precison(&res, (*mody)->precision_len, ft_strlen(num), (*mody)->flags[0]);

	if ((*mody)->flags[3] == 1 && ((*mody)->flags[4] == 1 || (*mody)->precision_len > 0))
		ft_make_0x_p(&res, 'x');
	ft_putstr(res);
	free(to_free);
	free(res);
}

void type_X(va_list *list, t_flags **mody)
{
	long int a;
	char *num;
	int res_len;
	char *res;
	char *to_free;
	
	if ((*mody)->type == 1)
		a = (unsigned char)va_arg(*list, long int);
	else if ((*mody)->type == 2)
		a = (unsigned short)va_arg(*list, long int);
	else if ((*mody)->type == 3)
		a = (unsigned long long)va_arg(*list, unsigned long long);
	else if ((*mody)->type == 4)
		a = (unsigned long)va_arg(*list, unsigned long);
	else if ((*mody)->type == 5)
		a = va_arg(*list, long int);
	else if ((*mody)->type == 6)
		a = (size_t)va_arg(*list, size_t);
	else
		a = (unsigned int)va_arg(*list, long int);
	num =  ft_itoa_base_u(a, 16, 'A');
	to_free = num;
	if (num[0] == '0' && num[1] == '\0' && (*mody)->spec_flag == 0)
		num++;
	if ((*mody)->flags[1] == 1)
		(*mody)->flags[1] = 0;
	if ((*mody)->flags[3] == 1 && num[1] != '\0')
	{
		ft_realochex(&num, 'X', &to_free);
		(*mody)->precision_len += 2;
		to_free = num;
		(*mody)->precision_len += 2;
	}
	if (num[0] == '-')
	{
		(*mody)->flags[1] = 0;
		(*mody)->flags[2] = 0;
	}
	if ((*mody)->flags[0] == 1)
		(*mody)->flags[4] = 0;
	if ((*mody)->flags[4] == 1 && ((*mody)->precision_len > 2))
		(*mody)->flags[4] = 0;
	res_len = (*mody)->precision_len <= (*mody)->width_len ? (*mody)->width_len : (*mody)->precision_len;
	if ((num[0] == '-' || (*mody)->flags[1] == 1) && (*mody)->precision_len >= (int)ft_strlen(num))
	{
		if ((*mody)->width_len <= (*mody)->precision_len)
			res_len++;
		if ((*mody)->flags[1] != 1)
			(*mody)->precision_len++;
	}
	if (res_len < (int)ft_strlen(num))
	{
		res_len = ft_strlen(num);
		if ((*mody)->flags[1] == 1)
			res_len++;
	}
	res = (char*)malloc(sizeof(char) * (res_len + 1));
	res[res_len] = 0;
	res_len--;
	while (res_len != -1)
		res[res_len--] = ' ';
	(*mody)->precision_len -= ft_strlen(num);
	(*mody)->width_len -= ft_strlen(num);
	if ((*mody)->precision_len > 0 && (*mody)->width_len > 0 && (*mody)->width_len > (*mody)->precision_len)
		(*mody)->width_len -= (*mody)->precision_len;
	if ((*mody)->flags[4] == 1)
		ft_write_zeros(&res,(*mody)->width_len, (*mody)->flags[1], a);
	if ((*mody)->flags[4] == 0)
		ft_write_spaces(&res,(*mody)->width_len, (*mody)->flags[0]);
	ft_write_num(&res, num, (*mody)->flags[0], (*mody)->flags[1]);
	if ((*mody)->precision_len > 0)
		write_precison(&res, (*mody)->precision_len, ft_strlen(num), (*mody)->flags[0]);
	if ((*mody)->flags[3] == 1 && ((*mody)->flags[4] == 1 || (*mody)->precision_len > 0))
		ft_make_0x_p(&res, 'X');
	ft_putstr(res);
	free(to_free);
	free(res);
}

void type_c(va_list *list, t_flags **mody)
{
	char c;
	char filler = ' ';

	if ((*mody)->width_len < 0)
	{
		(*mody)->width_len *= -1;
		(*mody)->flags[0] = 1;
	}
	if ((*mody)->type == 4)
	{
		type_C(list, &(*mody));
		return ;
	}
	c = va_arg(*list, int);
	if ((*mody)->width_len > 0 && (*mody)->flags[0] == 1)
	{
		ft_putchar(c);
		while (--(*mody)->width_len)
		{
			ft_putchar(filler);
		}
		return ;
	}
	if ((*mody)->width_len > 0 & (*mody)->flags[0] != 1)
	{
		if ((*mody)->flags[4] == 1)
			filler = '0';
		while (--(*mody)->width_len)
			ft_putchar(filler);
		ft_putchar(c);
		return ;
	}
	ft_putchar(c);
}

void type_C(va_list *list, t_flags **mody)
{

	//type_c(list, &(*mody));

	wchar_t c;

	*mody = *mody;
	c = va_arg(*list, wchar_t);
	// if ((*mody)->width_star)
	// 	(*mody)->width_len = va_arg(*list, int);
	// if ((*mody)->width_len > 0 && (*mody)->flags[0] == 1)
	// {
	// 	ft_putwchar(c);
	// 	while (--(*mody)->width_len)
	// 		ft_putwchar(' ');
	// 	return ;
	// }
	// if ((*mody)->width_len > 0 & (*mody)->flags[0] != 1)
	// {
	// 	while (--(*mody)->width_len)
	// 		ft_putwchar(' ');
	// 	ft_putwchar(c);
	// 	return ;
	// }
	ft_putwchar(c);
}

void type_error(char *tmp, t_flags **mody)
{
	int res_len;
	char *res;

	if (tmp == 0)
	{
		ft_putstr("(null)");
		return ;
	}
	if ((*mody)->flags[1] == 1)
		(*mody)->flags[1] = 0;
	if ((*mody)->flags[0] == 1)
		(*mody)->flags[4] = 0;
	if ((*mody)->flags[4] == 1 && ((*mody)->precision_star > 0 || (*mody)->precision_len > 0))
		(*mody)->flags[4] = 0;
	if (tmp[0] == '\0')
		(*mody)->precision_len = 0;
	res_len = (*mody)->precision_len <= (*mody)->width_len ? (*mody)->width_len : (*mody)->precision_len;
	if ((*mody)->precision_len >= 0 && (*mody)->precision_len < (int)ft_strlen(tmp))
		write_precison_str(&tmp, &(*mody), (int)ft_strlen(tmp));
	if ((tmp[0] == '-' || (*mody)->flags[1] == 1) && (*mody)->precision_len >= (int)ft_strlen(tmp))
	{
		if ((*mody)->width_len <= (*mody)->precision_len)
			res_len++;
		if ((*mody)->flags[1] != 1)
			(*mody)->precision_len++;
	}
	if (res_len < (int)ft_strlen(tmp))
	{
		res_len = ft_strlen(tmp);
		if ((*mody)->flags[1] == 1)
			res_len++;
	}
	res = (char*)malloc(sizeof(char) * (res_len + 1));
	res[res_len] = 0;
	res_len--;
	while (res_len != -1)
		res[res_len--] = ' ';
	(*mody)->width_len -= ft_strlen(tmp);
	if ((*mody)->flags[4] == 0)
		ft_write_spaces(&res,(*mody)->width_len, (*mody)->flags[0]);
	if ((*mody)->flags[4] == 1)
		ft_write_zeros(&res,(*mody)->width_len, (*mody)->flags[0], 0);
	ft_write_num(&res, tmp, (*mody)->flags[0], (*mody)->flags[1]);
	g_str = ft_strjoin(g_str, res);
	free(tmp);
	ft_putgstr();

	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//HELP FUNCS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char	*ft_strjoin(char *s1, char *s2)
{
	char			*res;
	unsigned int	i;
	unsigned int	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	res = (char*)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (res == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_strlen(s1))
	{
		res[i] = s1[i];
		i++;
	}
	while (j < ft_strlen(s2))
		res[i++] = s2[j++];
	res[i] = '\0';
	free(s1);
	free(s2);
	return (res);
}


char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*res;
	unsigned int	i;
	unsigned int	end;

	if (s == NULL)
		return (NULL);
	res = (char*)malloc(sizeof(char) * len + 1);
	if (res == NULL)
		return (NULL);
	i = 0;
	end = start + len;
	while (start < end)
	{
		res[i] = s[start];
		i++;
		start++;
	}
	res[i] = 0;
	return (res);
}

char	*ft_strdup(const char *s1)
{
	char	*res;
	int		i;
	int 	j;

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


void	ft_write_num(char **res, char *num, int alignment, int plus)
{
	int i;
	int j;
	i = 0;

	if (num[0] == '\0')
		return ;
	if (alignment == 1)
	{
		j = plus == 1 ? 1 : 0;
		(*res)[0] = (plus == 1) ? '+' : ' ';
		while (num[i])
		{
			(*res)[j++] = num[i++];
		}
	}
	if (alignment == 0)
	{
		j = ft_strlen(*res) - 1;
		i = ft_strlen(num) - 1;
		while (i > 0)
		{
			(*res)[j--] = num[i--];
		}
		if ((*res)[0] != '-')
			(*res)[j] = num[i];
		if (plus == 1 && res[0][0] != '+')
			(*res)[--j] = '+';
	}
}

void	ft_make_0x_p(char **str, char c)
{
	int j;
	int i;
	int count_zeros;
	char *tmp;

	tmp = (char*)malloc(sizeof(char) * ft_strlen(*str));
	i = 0;
	j = 0;
	count_zeros = 0;

	while((*str)[i] == ' ')
		i++;
	while((*str)[i++] == '0')
		count_zeros++;
	count_zeros--;
	while ((*str)[i])
		tmp[j++] = (*str)[i++];
	tmp[j] = 0;
	i = 0;
	j = 0;
	while((*str)[i] == ' ')
		i++;
	(*str)[i++] = '0';
	(*str)[i++] = c;
	while(count_zeros--)
		(*str)[i++] = '0';
	while (tmp[j])
		(*str)[i++] = tmp[j++];
	free(tmp);
}

void	ft_make_0x(char **str, char c)
{
	char	*tmp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if ((*str) == 0 || str == 0)
		return ;
	if (!(tmp = (char*)malloc(sizeof(char) * (ft_strlen(*str)))))
		return ;
	while ((*str)[j])
		tmp[i++] = (*str)[j++];
	tmp[i] = 0;
	free((*str));
	if (!(*str = (char*)malloc(sizeof(char) * (ft_strlen(tmp) + 2))))
		return ;
	(*str)[0] = '0';
	(*str)[1] = c;
	i = 2;
	j = 2;
	while (tmp[j])
	{
		if (tmp[j] == 'x')
		{
			(*str)[i++] = '0';
			j++;
		}
		(*str)[i++] = tmp[j++];
	}
	(*str)[i] = 0;
	free(tmp);
	return ;
}

void	write_precison(char **str, int i, int num_len, int alig)
{
	int str_len;
	int minus;
	int a; 
	int j;

	minus = 0;
	if (i <= 0)
			return ;
	if (alig == 0)
	{
		str_len = ft_strlen(*str) - num_len - 1;
		if ((*str)[str_len + 1] == '-')
		{
			minus = 1;
			str_len++;
		}
		if ((*str)[str_len] == '+')
		{
			minus = 2;
			//i--;
		}
		while (i--)
			(*str)[str_len--] = '0';
		if (minus == 1)
			(*str)[str_len] = '-';
		if (minus == 2)
		{
			if (str_len < 0)
				str_len = 0;
			(*str)[str_len] = '+';
		}
		return ;
	}
	if ((*str)[0] == '-' || (*str)[0] == '+')
	{
		j = 1;
		i++;
	}
	else
		j = 0;
	a = ((*str)[0] == '-' || (*str)[0] == '+') ? 1 : 0;
	if ((*str)[0] == '+')
	{
		num_len++;
	}
	ft_memmove((*str) + i, (*str) + a, num_len - a);
	i -= a;
	while(i--)
		(*str)[j++] = '0';
}

void	ft_write_zeros(char **str, int i, int plus, int minus)
{
	int j;
	int delimit;

	delimit = 0;
	if (i <= 0)
		return ;
	j = 0;
	if (minus < 0)
	{
		(*str)[0] = '-';
		delimit = 1;
		i++;
		j++;
	}
	while (i-- > delimit)
		(*str)[j++] = '0';
	if (plus)
		(*str)[0] = '+';
}

void	ft_write_spaces(char **str, int i, int alignment)
{
	int j;

	if (i <= 0)
		return ;
	if (alignment == 0)
	{
		j = 0;
		while (i--)
			(*str)[j++] = ' ';
		return ;
	}
	if (alignment == 1)
	{
		j = ft_strlen(*str) - 1;
		while (i--)
			(*str)[j--] = ' ';
		return ;
	}
}

int		num_len(int n)
{
	int i;

	n = n < 0 ? n * -1 : n;
	i = 1;

	while ((n /= 10))
		i++;
	
	return (i);
}

void	ft_putchar(char c)
{
	g_ret++;
	write(1, &c, sizeof(c));
}

void	ft_putstr(char const *str)
{
	if (str == NULL)
		return ;
	while (*str != '\0')
	{
		ft_putchar(*str);
		str++;
	}
}

void	ft_putwchar(wchar_t c)
{
	// 	простые чарики, уровень первый, 7 заполненых битов (от 0 до 127)				
	if (c < 128) //  0xxx-xxxx - так нужно зашифровать
		ft_putchar(c);

	//	юникод, уровень второй (дву символьный), 11 заполеных битов	(от 128 до 2047)
	if (c > 127 && c < 2048) // 110x-xxxx 10xx-xxxx - так нужно зашифвровать, очередность с головы
	{
		ft_putchar((c >> 6) + 192); // 
		ft_putchar((c & 63) + 128);
	}

	// юникод, уровень тертий (трёх символьный) , 16 заполеных битов (от 2048 до 65535)
	if (c > 2047 && c < 65536) // 1110-xxxx 10xx-xxxx 10xx-xxxx - так нужно зашифровать, очередность с головы
	{
		ft_putchar((c >> 12) + 224);
		ft_putchar(((c >> 6) & 63) + 128);
		ft_putchar((c & 63) + 128);
	}
	// юникод, уровень четвертый (4 символьный), 21 заполененый бит (от 65536 до 2097151)
	if (c > 65535 && c < 2097152) // 1111-0xxx 10xx-xxxx 10xx-xxxx 10xx-xxxx - так нужно зашифровать, очередность с головы
	{
		ft_putchar((c >> 18) + 240);	// при помощи побитового сдвига получаем первые три бита и к ним добавляем 1111-0 (240) = первому зашифрованому в юникод символу

		ft_putchar(((c >> 12) & 63) + 128); // при помощи побитового сдвига получаем доступ к предыдущим 6 битам применяем побитовое & что бы получить только совпавшие биты
													// биты числа 63 : (00111111) после чего добавляем к результату верхушку из (10xx-xxxx) число (128)

		ft_putchar(((c >> 6) & 63) + 128);  // при помощи побитового сдвига получаем доступ к предыдущим 6 битам применяем побитовое & что бы получить только совпавшие биты
											        // биты числа 63 : (00111111) после чего добавляем к результату верхушку из (10xx-xxxx) число (128)

		ft_putchar((c & 63) + 128);			//теперь приняем маску 63 к последним битам в нашей очереди и добавляет верхушку (10xx-xxxx)
	}

}

void	ft_putwstr(wchar_t const *str)
{
	if (str == NULL)
		return ;
	while (*str != '\0')
	{
		ft_putwchar(*str);
		str++;
	}
}

char	*remove_zeros(char **str, int neg)
{
	char *new;
	int i;
	int j;

	i = 0;
	j = 0;
	new = (char*)malloc(sizeof(char) * 25);
	if(*str)
	{
		if (neg == 1)
		{
			new[i++] = ' ';
			j++;
			while ((*str)[j] == '0')
				j++;
			while((*str)[j])
				new[i++] = (*str)[j++];
			new[i] = 0;
		free(*str);
		return (new);
		}
		while ((*str)[j] == '0')
			j++;
		while((*str)[j])
			new[i++] = (*str)[j++];
		new[i] = 0;
	}
	free(*str);
	return (new);
}

char	*ft_itoa_base(long long int value, int base)
{
	int						i;
	char					*nbr;
	int						neg;
	unsigned long long int	r;
	neg = 0;
	if (value < 0)
	{
		if (base == 10)
			neg = 1;
		r = value * -1;
	}
	else
	{
		r = value;
	}
	i = 25;
	nbr = (char*)malloc(sizeof(char) * i);
	nbr[i + neg] = '\0';
	if (value == 0)
	{
		nbr[0] = '0';
		nbr[1] = '\0';
		return (nbr);
	}
	while (i-- > 0)
	{
		nbr[i + neg] = (r % base) + (r % base > 9 ? 'a' - 10 : '0');
		r = r / base;
	}
	nbr = remove_zeros(&nbr, neg);
	if (neg)
		nbr[0] = '-';
	return (nbr);
}

char	*ft_itoa_base_u(unsigned long int value, int base, char later)
{
	int		i;
	char	*nbr;

	i = 25;
	nbr = (char*)malloc(sizeof(char) * i);
	nbr[i] = '\0';
	if (value == 0)
	{
		nbr[0] = '0';
		nbr[1] = 0;
		return (nbr);
	}
	while (i-- > 0)
	{
		nbr[i] = (value % base) + (value % base > 9 ? later - 10 : '0');
		value = value / base;
	}
	nbr = remove_zeros(&nbr, 0);
	return (nbr);
}

size_t	ft_strlen(const char *s)
{
	size_t res;

	res = 0;
	while (*s != '\0' && ++res)
		s++;
	return (res);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char *ds;

	ds = (unsigned char*)dst;
	if (dst > src)
	{
		while (len--)
			*((unsigned char*)dst + len) = *((unsigned char*)src + len);
	}
	else
	{
		while (len--)
		{
			*((unsigned char*)dst) = *((unsigned char*)src);
			dst++;
			src++;
		}
	}
	return (ds);
}

int		ft_wcharlen(wchar_t *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int 	ft_wstrlen(wchar_t *str)
{
	int i;
	int res;

	i = 0;
	res = 0;
	while (str[i])
	{
		if (str[i] < 128)
			res +=1;
		if (str[i] > 127 && str[i] < 2048)
			res +=2;
		if (str[i] > 2047 && str[i] < 65536)
			res +=3;
		if (str[i] > 65535 && str[i] < 2097152)
			res +=4;
		i++;
	}
	return (res);
}

wchar_t 	*ft_duplic_wchr(wchar_t *str)
{
	int i;
	wchar_t *res;

	if (str == 0)
		return (0);
	i = 0;
	res = (wchar_t*)malloc(sizeof(wchar_t) * ft_wstrlen(str) + sizeof(wchar_t));
	while (*str)
		res[i++] = *str++;
	res[i] = 0;
	return (res);
}

//////////////////////////////////////////////////////////////////////////////////////
				//READ FORMATING//
//////////////////////////////////////////////////////////////////////////////////////

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


int		iis(char c, t_flags **formatt)
{
	if (c == ' ' || c == '#' || c == '-' || c == '+')
	{
		check_flags(c,  &(*formatt));
		return (1);
	}
	else
		return (0);
}

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


void	check_width(char **str, t_flags **formatt, va_list **list)
{
	int res;

	res = 0;
	while (**str && ((**str >= '0' && **str <= '9') || iis(**str, &(*formatt)) || **str == '*'))
	{
		if (**str >= '0' && **str <= '9')
		{
			if (*(*str - 1) == '*')
				res = 0;
			res = (**str - 48) + (res * 10);
		}
		if (**str == '*')
		{
			res = va_arg(**list, int);
		}
		(*str)++;
	}
		(*formatt)->width_len = res;
}

void	check_precision(char **str, t_flags **formatt, va_list **list)
{
	int res;

	(*str)++;
	res = 0;
		while (**str && ((**str >= '0' && **str <= '9') || iis(**str, &(*formatt)) || **str == '*'))
		{
			if (**str >= '0' && **str <= '9')
			{
				if (*(*str - 1) == '*')
				{
					res = 0;
				}
				res = (**str - 48) + (res * 10);
			}
			if (**str == '*')
			{
				res = va_arg(**list, int);
			}
			(*str)++;
		}
		(*formatt)->precision_len = res;

	if (res == 0)
		(*formatt)->spec_flag = 0;
}

void	check_type(char **str, t_flags **formatt)
{
	if (**str == 'h' && *(*str + 1) == 'h')
		(*formatt)->type = 1;
	if (**str == 'h' && *(*str + 1) != 'h')
		(*formatt)->type = 2;
	if (**str == 'l' && *(*str + 1) == 'l')
		(*formatt)->type = 3;
	if (**str == 'l' && *(*str + 1) != 'l')
		(*formatt)->type = 4;
	if (**str == 'j')
		(*formatt)->type = 5;
	if (**str == 'z')
		(*formatt)->type = 6;
	if ((*formatt)->type == 3 || (*formatt)->type == 1)
		(*str)++;
	(*str)++;
	while (iis(**str, &(*formatt)))
		(*str)++;
}

t_flags		*ft_format(char **str, va_list *list)
{
	t_flags *formatt;
	char	*tmp;
	char *types = "sSpdDioOuUxXcC% ";

	tmp = (*str) - 1;
	init_format(&formatt);
	while (**str && (**str == '-' || **str == '+' || **str == ' ' || **str == '#' || **str == '0'))
	{
		check_flags(*(*str)++, &formatt);
	}
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
	{
		tmp = (*str);
		while (*(*str) && *(*str) != '%')
			(*str)++;
		type_error(ft_strsub(tmp, 0, 1), &formatt);
		formatt->error = 1;
		if (*tmp)
			tmp++;
		while (*tmp && *tmp != '%')
			ft_putchar(*tmp++);
	}
	return (formatt);
}

