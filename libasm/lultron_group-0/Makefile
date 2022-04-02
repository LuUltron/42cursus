# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lultron <lultron@student.21-school.r>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/01 02:11:56 by lultron           #+#    #+#              #
#    Updated: 2020/05/29 10:11:13 by lultron          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libasm.a

SRC = ft_strlen.s ft_strcpy.s ft_strcmp.s ft_strdup.s ft_write.s ft_read.s

OBJ = $(SRC:.s=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)
	ranlib $(NAME)

%.o: %.s
	nasm -fmacho64 -I. -s $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f libasm_tester
	# rm -f test

re: fclean all

test: all
	# @touch test
	# @echo "test" > test
	gcc -Wall -Wextra -Werror -I./libasm.h libasm.a main.c -o libasm_tester
	./libasm_tester