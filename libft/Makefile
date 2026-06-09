NAME = libft.a
CC = cc

FLAGS = -Wall -Werror -Wextra

SRCS_DIR = srcs/
LIBFT = libft/
FT_PRINTF = ft_printf/
GET_NEXT_LINE = get_next_line/

OBJS_DIR = objs/

HEADER = libft.h

SRCS = $(SRCS_DIR)$(LIBFT)ft_isalpha.c \
		$(SRCS_DIR)$(LIBFT)ft_isdigit.c \
		$(SRCS_DIR)$(LIBFT)ft_isalnum.c \
		$(SRCS_DIR)$(LIBFT)ft_isascii.c \
		$(SRCS_DIR)$(LIBFT)ft_isprint.c \
		$(SRCS_DIR)$(LIBFT)ft_strlen.c \
		$(SRCS_DIR)$(LIBFT)ft_memset.c \
		$(SRCS_DIR)$(LIBFT)ft_bzero.c \
		$(SRCS_DIR)$(LIBFT)ft_memcpy.c \
		$(SRCS_DIR)$(LIBFT)ft_memmove.c \
		$(SRCS_DIR)$(LIBFT)ft_strlcpy.c \
		$(SRCS_DIR)$(LIBFT)ft_strlcat.c \
		$(SRCS_DIR)$(LIBFT)ft_toupper.c \
		$(SRCS_DIR)$(LIBFT)ft_tolower.c \
		$(SRCS_DIR)$(LIBFT)ft_strchr.c \
		$(SRCS_DIR)$(LIBFT)ft_strrchr.c \
		$(SRCS_DIR)$(LIBFT)ft_strncmp.c \
		$(SRCS_DIR)$(LIBFT)ft_memchr.c \
		$(SRCS_DIR)$(LIBFT)ft_memcmp.c \
		$(SRCS_DIR)$(LIBFT)ft_strnstr.c \
		$(SRCS_DIR)$(LIBFT)ft_atoi.c \
		$(SRCS_DIR)$(LIBFT)ft_calloc.c \
		$(SRCS_DIR)$(LIBFT)ft_strdup.c \
		$(SRCS_DIR)$(LIBFT)ft_substr.c \
		$(SRCS_DIR)$(LIBFT)ft_strjoin.c \
		$(SRCS_DIR)$(LIBFT)ft_strtrim.c \
		$(SRCS_DIR)$(LIBFT)ft_split.c \
		$(SRCS_DIR)$(LIBFT)ft_itoa.c \
		$(SRCS_DIR)$(LIBFT)ft_strmapi.c \
		$(SRCS_DIR)$(LIBFT)ft_striteri.c \
		$(SRCS_DIR)$(LIBFT)ft_putchar_fd.c \
		$(SRCS_DIR)$(LIBFT)ft_putstr_fd.c \
		$(SRCS_DIR)$(LIBFT)ft_putendl_fd.c \
		$(SRCS_DIR)$(LIBFT)ft_putnbr_fd.c \
		$(SRCS_DIR)$(LIBFT)ft_realloc.c \
		$(SRCS_DIR)$(LIBFT)ft_memcpy_opti_af.c \
		$(SRCS_DIR)$(LIBFT)ft_realloc_array.c \
		$(SRCS_DIR)$(LIBFT)ft_free_array.c \
		$(SRCS_DIR)$(LIBFT)ft_free_array_of_array.c \
		$(SRCS_DIR)$(LIBFT)ft_get_array_length.c \
		$(SRCS_DIR)$(LIBFT)ft_strnlen.c \
		$(SRCS_DIR)$(LIBFT)ft_str_has_exactly.c \
		$(SRCS_DIR)$(LIBFT)ft_strcmp.c \
		\
		$(SRCS_DIR)$(FT_PRINTF)ft_printf.c \
		$(SRCS_DIR)$(FT_PRINTF)base_utils.c \
		$(SRCS_DIR)$(FT_PRINTF)print_functions.c \
		$(SRCS_DIR)$(FT_PRINTF)print_functions2.c \
		\
		$(SRCS_DIR)$(GET_NEXT_LINE)get_next_line.c \

OBJS = $(patsubst $(SRCS_DIR)%.c,$(OBJS_DIR)%.o,$(SRCS))

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c $(HEADER) | $(OBJS_DIR)
	@$(CC) $(FLAGS) -o $@ -c $<
	@echo "Compiling $<"

$(NAME): $(OBJS) $(HEADER)
	@ar rcs $(NAME) $(OBJS)

$(OBJS_DIR) :
	@mkdir -p $(OBJS_DIR)$(LIBFT)
	@mkdir -p $(OBJS_DIR)$(FT_PRINTF)
	@mkdir -p $(OBJS_DIR)$(GET_NEXT_LINE)

all : $(NAME)

clean :
	@rm -rf $(OBJS_DIR)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re