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

CC = gcc 

OBJ = ft_printf.o ft_decimal.o ft_format.o ft_format_struct.o ft_strlen.o ft_memmove.o ft_putchar.o ft_putnbr.o ft_putstr.o


all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

%.o: %.c
	$(CC) -o $@ -c $< $(FLAGS)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
