CC		= gcc
CFLAGS	= -Wall -Werror -Wextra

NAME	= libft.a
INCPATH	= includes/
HEADERS	= $(addprefix $(INCPATH), libft.h)
SOURCES	= $(addprefix src/, \
			ft_memcpy.c \
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
