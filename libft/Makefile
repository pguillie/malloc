#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/15 11:22:20 by pguillie          #+#    #+#              #
#    Updated: 2018/09/19 18:07:52 by pguillie         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra

NAME	= libft.a
INCPATH	= includes/
HEADERS	= $(addprefix $(INCPATH), libft.h)
SOURCES	= $(addprefix src/, \
			ft_bzero.c \
			ft_memcpy.c \
			ft_putnbr.c \
			ft_putptr.c \
			ft_putstr.c \
			ft_strlen.c \
			)
OBJECTS	= $(SOURCES:src/%.c=obj/%.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): obj $(OBJECTS)
	@ echo "Compiling $(NAME) library..."
	ar rc $@ $(OBJECTS)
	ranlib $@
	@ echo "$(NAME) successfully compiled"

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -I $(INCPATH) -o $@ -c $<

obj:
	@ echo "Creating $(NAME) objects directory..."
	mkdir obj

clean:
	@ echo "Removing $(NAME) object files..."
	rm -rf obj

fclean:
	@ echo "Removing $(NAME) all compiled files..."
	rm -rf obj $(NAME)

re: fclean all
