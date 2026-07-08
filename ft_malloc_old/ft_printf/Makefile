NAME = libftprintf.a
CC = cc
FLAGS = -Wall -Werror -Wextra

SRCS = ft_printf.c \
		base_utils.c \
		print_functions.c \
		print_functions2.c \

OBJS = $(SRCS:.c=.o)

%.o : %.c
	$(CC) $(FLAGS) -o $@ -c $<

$(NAME) : $(OBJS)
	ar rcs $(NAME) $(OBJS)
#	ranlib $(NAME)

a.out : $(OBJS)
	 $(CC) $(FLAGS) -o $@ $^

all : $(NAME)

.PHONY: clean
clean :
	rm -f *.o

.PHONY: fclean
fclean : clean
	rm -f $(NAME)
	rm -f a.out

.PHONY: re
re : fclean all