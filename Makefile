ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LINK = libft_malloc.so

CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIC
DEPFLAGS = -MMD -MP
INCLUDES = -I include
LDFLAGS = -shared

SRCS_DIR = src/
OBJS_DIR = objs/

SRCS = $(SRCS_DIR)alloc/malloc.c \
	$(SRCS_DIR)alloc/realloc.c \
	$(SRCS_DIR)alloc/calloc.c \
	$(SRCS_DIR)alloc/free.c \
	$(SRCS_DIR)show_alloc_mem.c \
	$(SRCS_DIR)allocator.c \
	$(SRCS_DIR)align.c \
	$(SRCS_DIR)zone.c \
	$(SRCS_DIR)zone_utils.c \
	$(SRCS_DIR)block.c \
	$(SRCS_DIR)block_utils.c \
	$(SRCS_DIR)utils/ft_memcpy.c \
	$(SRCS_DIR)utils/ft_memset.c \
	$(SRCS_DIR)utils/print_utils.c

OBJS = $(patsubst $(SRCS_DIR)%.c,$(OBJS_DIR)%.o,$(SRCS))

DEPS = $(OBJS:.o=.d)

all: $(NAME) $(LINK)

$(NAME): $(OBJS)
	@echo "Linking $@"
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS)

$(LINK): $(NAME)
	@ln -sf $(NAME) $(LINK)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(@D)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) $(INCLUDES) $(DEPFLAGS) -o $@ -c $<

clean:
	@rm -rf $(OBJS_DIR)

fclean: clean
	@rm -f $(NAME) $(LINK)

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)
