ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LINK = libft_malloc.so
EXAMPLE_NAME = example
EXAMPLE_SRC = example.c

CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIC -pthread -fvisibility=hidden
DEPFLAGS = -MMD -MP
INCLUDES = -I include
LDFLAGS = -shared -pthread

SRCS_DIR = src/
OBJS_DIR = objs/

SRCS = $(SRCS_DIR)malloc/malloc.c \
	$(SRCS_DIR)malloc/malloc_internal.c \
	$(SRCS_DIR)realloc/realloc.c \
	$(SRCS_DIR)realloc/realloc_internal.c \
	$(SRCS_DIR)calloc/calloc.c \
	$(SRCS_DIR)free/free.c \
	$(SRCS_DIR)free/free_internal.c \
	$(SRCS_DIR)show_alloc_mem/show_alloc_mem.c \
	$(SRCS_DIR)show_alloc_mem/show_alloc_mem_internal.c \
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

$(EXAMPLE_NAME): $(EXAMPLE_SRC) $(LINK)
	@echo "Linking $@"
	$(CC) -Wall -Wextra -Werror -o $@ $(EXAMPLE_SRC) -ldl

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(@D)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) $(INCLUDES) $(DEPFLAGS) -o $@ -c $<

clean:
	@rm -rf $(OBJS_DIR)

fclean: clean
	@rm -f $(NAME) $(LINK) $(EXAMPLE_NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)
