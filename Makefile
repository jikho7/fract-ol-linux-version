# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/01 17:17:52 by jdefayes          #+#    #+#              #
#    Updated: 2023/02/06 16:52:32 by jdefayes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME   	= fractol
CFLAGS = -Wall -Wextra -Werror
IFLAGS_LINUX = -Llibft -lmlx -lXext -lX11 -lm -Lmlx
IFLAGS = -lmlx -lft -Llibft -Lmlx -framework OpenGL -framework Appkit
CC     = gcc $(CFLAGS)
SRC		=	main.c\
			hooks.c\
			utils.c\
			draw.c\
			fractales.c\
			window.c\

OBJ		= ${SRC:.c=.o}
LIB    = libft/libft.a
MLX    = mlx/libmlx.a
INCLUDE = -Ilibft -Imlx

.c.o:
	$(CC) -c $< -o $@ $(INCLUDE)

$(NAME): $(MLX) $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(INCLUDE) $(IFLAGS_LINUX)

all: $(NAME)

$(MLX):
	$(MAKE) -C mlx

clean:
	$(RM) $(OBJ)
	$(MAKE) -C mlx clean

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

