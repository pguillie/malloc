#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/15 12:56:13 by pguillie          #+#    #+#              #
#    Updated: 2018/08/15 16:03:27 by pguillie         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif
NAME	= libft_malloc_$(HOSTTYPE).so
SOLINK	= libft_malloc.so
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -fpic
INCPATH	= includes/
HEADERS	= $(addprefix $(INCPATH), malloc.h)
LIBPATH	= libft/
LIB		= $(LIBPATH)libft.a

SOURCES	= $(addprefix src/, \
			free.c \
			free_large.c \
			free_small.c \
			free_tiny.c \
			get_chunk.c \
			malloc.c \
			malloc_init.c \
			malloc_large.c \
			malloc_small.c \
			malloc_tiny.c \
			malloc_top.c \
			malloc_verbose.c \
			realloc.c \
			)

OBJECTS	= $(SOURCES:src/%.c=obj/%.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): obj $(LIB) $(OBJECTS)
	@ echo "Compiling $(NAME) shared library..."
	$(CC) -shared $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIB)
	rm -f $(SOLINK) && ln -s $(NAME) $(SOLINK)
	@ echo "$(NAME) successfully compiled"

obj/%.o: src/%.c $(HEADERS) Makefile
	$(CC) $(CFLAGS) -I $(INCPATH) -o $@ -c $<

obj:
	@ echo "Creating $(NAME) objects directory..."
	mkdir obj

$(LIB):
	make -C $(LIBPATH)

clean:
	@ echo "Removing $(NAME) object files..."
	make -C $(LIBPATH) clean
	rm -rf obj

fclean:
	@ echo "Removing $(NAME) all compiled files..."
	make -C $(LIBPATH) fclean
	rm -rf obj $(NAME) $(SOLINK)

re: fclean all
