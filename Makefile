#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/15 12:56:13 by pguillie          #+#    #+#              #
#    Updated: 2018/09/25 12:46:51 by pguillie         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif
NAME	= libft_malloc_$(HOSTTYPE).so
SOLINK	= libft_malloc.so
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -fpic
DEBUG	= -g3 -fsanitize=address
INCPATH	= includes/
HEADERS	= $(addprefix $(INCPATH), malloc.h malloc_struct.h malloc_debug_var.h)
LIBPATH	= libft/
LIB		= $(LIBPATH)libft.a

SOURCES	= $(addprefix src/, \
			abort.c \
			calloc.c \
			free.c \
			get_chunk.c \
			malloc.c \
			malloc_init.c \
			malloc_small_list_api.c \
			malloc_verbose.c \
			ptcalloc.c \
			ptfree.c \
			ptfree_large.c \
			ptfree_small.c \
			ptfree_tiny.c \
			ptmalloc.c \
			ptmalloc_large.c \
			ptmalloc_small.c \
			ptmalloc_tiny.c \
			ptmalloc_top.c \
			ptrealloc.c \
			ptrealloc_large.c \
			ptrealloc_relocate.c \
			ptrealloc_small.c \
			ptrealloc_tiny.c \
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
