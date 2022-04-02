# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lultron <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/22 00:35:33 by lultron           #+#    #+#              #
#    Updated: 2020/07/22 00:36:01 by lultron          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
LIBFT = libft/libft.a
LIBFT_DIR = libft

INCLUDES = ft_printf.h
SRC = ft_printf.c parse_spec.c print_cspx.c print_diu.c
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME): $(OBJ) $(INCLUDES)
	@$(MAKE) -C $(LIBFT_DIR)
	@cp $(LIBFT) $(NAME)
	@ar rc $(NAME) $?
	@ranlib $(NAME)
	@echo libftprintf.a successfully created

%.o: %.c
	@clang -Wall -Wextra -Werror -c $< -o $@

clean:
	@echo clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	@rm -f $(OBJ)
	@echo ftprintf object files deleted

fclean: clean
	@echo fclean:
	@rm -f $(LIBFT)
	@echo libft.a deleted
	@rm -f $(NAME)
	@echo libftprintf.a deleted
	@echo ----------------------------------

re: fclean all

.PHONY: all clean fclean re
