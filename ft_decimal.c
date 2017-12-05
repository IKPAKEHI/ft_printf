
#include "ft_printf.h"


// void type_d(va_list *list, t_flags **mody)
// {
// 	char *num;
// 	int res_len;
// 	char *res;
// 	//printf("%d\n", (*mody)->precision_star);
// 	num = ft_itoa_base(va_arg(*list, int), 10);
// 	if (num[0] == '-') //если число негативное флаг space и + игнорируются
// 	{
// 		(*mody)->flags[1] = 0;
// 		(*mody)->flags[2] = 0;
// 	}
// 	if ((*mody)->flags[0] == 1) //если есть флаг - то флаг 0 игнорируестя
// 		(*mody)->flags[4] = 0;
// 	//если есть флаг 0 и указана точность, 0 игнорируется
// 	if ((*mody)->flags[4] == 1 && ((*mody)->precision_star > 0 || (*mody)->precision_len > 0))
// 		(*mody)->flags[4] = 0;
// 	if ((*mody)->precision_star)
// 		(*mody)->precision_len = va_arg(*list, int);
// 	if ((*mody)->width_star)
// 		(*mody)->width_len = va_arg(*list, int);
// 	res_len = (*mody)->precision_len <= (*mody)->width_len ? (*mody)->width_len : (*mody)->precision_len;
// 	if ((num[0] == '-' || (*mody)->flags[1] == 1) && (*mody)->precision_len >= (int)ft_strlen(num))
// 	{
// 		if ((*mody)->width_len <= (*mody)->precision_len)
// 			res_len++;
// 		if ((*mody)->flags[1] != 1)
// 			(*mody)->precision_len++;
// 	}
// 	if (res_len < (int)ft_strlen(num))
// 		res_len = (int)ft_strlen(num);
// 	res = (char*)malloc(sizeof(char) * (res_len + 1));
// 	res[res_len] = 0;
// 	res_len--;
// 	while (res_len != -1)
// 		res[res_len--] = ' ';
// 	(*mody)->precision_len -= (int)ft_strlen(num);
// 	(*mody)->width_len -= (int)ft_strlen(num);
// 	if ((*mody)->precision_len > 0 && (*mody)->width_len > 0 && (*mody)->width_len > (*mody)->precision_len)
// 		(*mody)->width_len -= (*mody)->precision_len;
// 	if ((*mody)->flags[4] == 1)
// 		ft_write_zeros(&res,(*mody)->width_len);
// 	if ((*mody)->flags[4] == 0)
// 		ft_write_spaces(&res,(*mody)->width_len, (*mody)->flags[0]);
// 	ft_write_num(&res, num, (*mody)->flags[0], (*mody)->flags[1]);
// 	if ((*mody)->precision_len > 0)
// 		write_precison(&res, (*mody)->precision_len, (int)ft_strlen(num), (*mody)->flags[0]);
// 	ft_putstr(res);
// }

