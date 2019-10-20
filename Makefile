# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlayna <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/21 17:58:59 by nlayna            #+#    #+#              #
#    Updated: 2019/08/11 07:12:40 by nlayna           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= fractol

SRCDIR	:= ./srcs/
INCDIR	:= ./includes/
LIBDIR	:= ./libft/
MLXDIR	:= ./mlx/
LIBINC	:= ./libft/includes/
HEADER  := $(INCDIR)fractol.h $(INCDIR)fractoldef.h

SRCS	:= main.c init.c render.c args.c reader.c utils.c hook.c
OBJ		:= main.o init.o render.o args.o reader.o utils.o hook.o
LIB		:= ./libft/libft.a \
			./mlx/libmlx.a

CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror
MLXF	:= -L $(MLXDIR) -lmlx -I $(MLXDIR) -framework OpenGL -framework Appkit -framework OpenCL

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ) $(LIB)
	$(CC) -g $(OBJ) -o $@ -I $(INCDIR) $(LIB) $(MLXF)

$(LIB):
	make -C $(LIBDIR)

%.o: $(SRCDIR)%.c $(HEADER)
	$(CC) $(CFLAGS) -I $(LIBINC) -I $(INCDIR) -c $< -o $@

clean:
	make clean -C $(LIBDIR)
	rm -rf *.o

fclean: clean
	make fclean -C $(LIBDIR)
	rm -rf $(NAME)

re: fclean all
