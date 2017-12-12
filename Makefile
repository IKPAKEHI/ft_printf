# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/06 14:39:42 by vlvereta          #+#    #+#              #
#    Updated: 2017/11/06 14:45:17 by vlvereta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = gcc -O3 -Wall -Wextra -Werror

OBJ = aluxuary_funcs/check_err_su.o aluxuary_funcs/ft_duplic_wchr.o aluxuary_funcs/ft_itoa_base.o \
	aluxuary_funcs/ft_itoa_base_u.o aluxuary_funcs/ft_make_0x_p.o aluxuary_funcs/ft_memmove.o aluxuary_funcs/ft_putstr.o \
	aluxuary_funcs/ft_putchar.o aluxuary_funcs/ft_putgstr.o aluxuary_funcs/ft_putgstr.o aluxuary_funcs/ft_putwchar.o \
	aluxuary_funcs/ft_putwstr.o aluxuary_funcs/ft_realoc_str.o aluxuary_funcs/ft_realochex.o aluxuary_funcs/ft_realooctal.o \
	aluxuary_funcs/ft_strdup.o aluxuary_funcs/ft_strjoin.o aluxuary_funcs/ft_strlen.o aluxuary_funcs/ft_strsub.o \
	aluxuary_funcs/ft_wcharlen.o aluxuary_funcs/ft_write_num.o aluxuary_funcs/ft_write_spaces.o aluxuary_funcs/ft_write_zeros.o \
	aluxuary_funcs/ft_wstrlen.o aluxuary_funcs/num_len.o aluxuary_funcs/remove_zeros.o aluxuary_funcs/write_precison.o \
	aluxuary_funcs/write_precison_str.o \
	format_handler/check_flags.o format_handler/check_precision.o format_handler/check_type.o format_handler/check_width.o \
	format_handler/ft_format.o format_handler/iis.o format_handler/init_format.o \
	type_handlers/type_error.o type_handlers/type_cu.o type_handlers/type_cc.o type_handlers/type_du.o type_handlers/type_i.o \
	type_handlers/type_interest.o type_handlers/type_ou.o type_handlers/type_oo.o type_handlers/type_p.o type_handlers/type_su.o type_handlers/type_ss.o \
	type_handlers/type_uuu.o type_handlers/type_uu.o type_handlers/type_xu.o type_handlers/type_xx.o type_handlers/type_dd.o\
	ft_printf.o

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

%.o: %.c
	$(CC) -o $@ -c $<

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
