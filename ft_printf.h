
#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdio.h>
# include <stdarg.h>

# include <stdlib.h>
# include <unistd.h>

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

typedef void funcs(va_list *list, t_flags **mody);

int				g_ret;
int				g_err;
char			*g_str;
int				g_i;
funcs*			g_f[16];
char			*g_types;

void			check_err_S(wchar_t *str);
wchar_t			*ft_duplic_wchr(wchar_t *str);
char			*ft_itoa_base(long long int value, int base);
char			*ft_itoa_base_u(unsigned long int value, int base, char later);
void			ft_make_0x_p(char **str, char c);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			ft_putchar(char c);
void			ft_putgstr(void);
void			ft_putstr(char const *str);
void			ft_putwchar(wchar_t c);
void			ft_putwstr(wchar_t const *str);
int				ft_realoc_str(char **str, int len);
void			ft_realochex(char **str, char c,char **to_free);
void			ft_realooctal(char **str, char c,char **to_free);
char			*ft_strdup(const char *s1);
char			*ft_strjoin(char *s1, char *s2);
size_t			ft_strlen(const char *s);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
int				ft_wcharlen(wchar_t *str);
void			ft_write_num(char **res, char *num, int alignment, int plus);
void			ft_write_spaces(char **str, int i, int alignment);
void			ft_write_zeros(char **str, int i, int plus, int minus);
int 			ft_wstrlen(wchar_t *str);
int				num_len(int n);
char			*remove_zeros(char **str, int neg);
void			write_precison(char **str, int i, int num_len, int alig);
void			write_precison_str(char **str, t_flags **mody, int str_len);

void			check_flags(char c, t_flags **formatt);
void			check_precision(const char **str, t_flags **formatt, va_list **list);
void			check_type(const char **str, t_flags **formatt);
void			check_width(const char **str, t_flags **formatt, va_list **list);
t_flags			*ft_format(const char **str, va_list *list);
int				iis(char c, t_flags **formatt);
void			init_format(t_flags **formatt);

void			type_interest(va_list *list, t_flags **mody);
void			type_s(va_list *list, t_flags **mody);
void			type_S(va_list *list, t_flags **mody);
void			type_p(va_list *list, t_flags **mody);
void			type_d(va_list *list, t_flags **mody);
void			type_D(va_list *list, t_flags **mody);
void			type_i(va_list *list, t_flags **mody);
void			type_o(va_list *list, t_flags **mody);
void			type_O(va_list *list, t_flags **mody);
void			type_u(va_list *list, t_flags **mody);
void			type_U(va_list *list, t_flags **mody);
void			type_x(va_list *list, t_flags **mody);
void			type_X(va_list *list, t_flags **mody);
void			type_c(va_list *list, t_flags **mody);
void			type_C(va_list *list, t_flags **mody);
void			type_error(char *tmp, t_flags **mody);

#endif
