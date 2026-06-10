ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LINK = libft_malloc.so

CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIC
DEPFLAGS = -MMD -MP
INCLUDES = -I includes -I libft
LDFLAGS = -shared
LDLIBS = -Llibft -lft

LIBFT_DIR = libft

SRCS_DIR = src/
OBJS_DIR = objs/

SRCS = $(SRCS_DIR)malloc.c

OBJS = $(patsubst $(SRCS_DIR)%.c,$(OBJS_DIR)%.o,$(SRCS))

DEPS = $(OBJS:.o=.d)

all: $(NAME) $(LINK)

$(NAME): $(OBJS)
	@echo "Starting LIBFT compilation"
	@$(MAKE) -s -C $(LIBFT_DIR)
	@echo "Linking $@"
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

$(LINK): $(NAME)
	@ln -sf $(NAME) $(LINK)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(@D)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) $(INCLUDES) $(DEPFLAGS) -o $@ -c $<

clean:
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@rm -rf $(OBJS_DIR)

fclean: clean
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@rm -f $(NAME) $(LINK)

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)
