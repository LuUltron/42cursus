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

GREEN	= \033[32m
BLUE	= \033[34m
NOCOLOR	= \033[0m

NAME		= cub3D
CC			= gcc
GDB			= -g -O2
WFLAGS		= -Werror -Wall -Wextra
INCLUDES	= -I srcs/
HEADERS		= cub3d.h

SRC_DIR		= srcs/
SRC_FILES	= main.c read_file.c parse_parameters.c read_map.c \
				trigger_events.c render.c render2.c sprites.c \
				cleaner.c cleaner2.c bmp.c
SRC			= $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ_DIR		= objs/
OBJ_FILES	= $(SRC_FILES:.c=.o)
OBJ			= $(addprefix $(OBJ_DIR), $(OBJ_FILES))

MLX_DIR		= minilibx_opengl/
MLX_FLAGS	= -l mlx -framework OpenGL -framework Appkit
LIBFT_DIR	= libft/
LIBFT		= libft/libft.a


all: libs $(OBJ_DIR) $(NAME)

libs:
	@echo "$(BLUE)<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>$(NOCOLOR)"
	@$(MAKE) -C $(LIBFT_DIR) bonus
	@$(MAKE) -C $(MLX_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(WFLAGS) -L$(MLX_DIR) $(MLX_FLAGS) $(I) -o $(NAME) $(LIBFT)
	@echo "$(GREEN)<<<<<<<<<<<<<<<<<< DONE! >>>>>>>>>>>>>>>>>>$(NOCOLOR)\n\
	Run $(BLUE)./cub3D [maps/filename.cub] [--save]\n$(NOCOLOR)\
	last argument optional to get a screenshot"
	@echo "$(GREEN)<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>$(NOCOLOR)\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(GDB) -c $< -o $@

clean:
	@echo "$(BLUE)<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>$(NOCOLOR)"
	@rm -rf $(OBJ_DIR)
	@make -C $(MLX_DIR) clean
	@make -C $(LIBFT_DIR) fclean
	@echo Object files erased

fclean: clean 
	@rm -rf $(NAME)
	@rm -rf $(NAME).bmp
	@echo Executable file and bmp erased
	@echo "$(GREEN)<<<<<<<<<<<<<<<< GOODBYE! >>>>>>>>>>>>>>>>>$(NOCOLOR)\n"

re: fclean all

.PHONY: all clean fclean re libs