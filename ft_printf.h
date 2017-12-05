
#ifndef FT_PRINTF_H
# define FT_PRINTF_H
#include <stdio.h>
#include <stdarg.h>

#include <stdlib.h>
#include <unistd.h>

int g_ret = 0;

typedef struct	s_flags
{
	int		flags[5];
	int		width_star;
	int		width_len;
	int		precision_star;
	int		precision_len;
	int		type;	
}				t_flags;


void		ft_putnbr(int n);
void		ft_putchar(char c);
void		ft_putstr(char const *str);
char		*ft_itoa_base(int value, int base);
char		*ft_itoa_base_u(unsigned int value, int base, char later);
void		ft_putnbr_u(unsigned int n);
t_flags		*ft_format(char **str);
int			num_len(int n);
void		ft_write_spaces(char **str, int i, int alignment);
void		ft_write_zeros(char **str, int i);
//char		*ft_itoa(int n);
int			ft_strlen(const char *s);
void		ft_write_num(char **res, char *num, int alignment, int plus);
void		write_precison(char **str, int i, int num_len, int alig);
void		*ft_memmove(void *dst, const void *src, size_t len);



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

#endif