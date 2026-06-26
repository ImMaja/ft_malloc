ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LINK = libft_malloc.so

FT_PRINTF_DIR = ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIC
DEPFLAGS = -MMD -MP
INCLUDES = -I include -I $(FT_PRINTF_DIR)
LDFLAGS = -shared

SRCS_DIR = src/
OBJS_DIR = objs/
TESTS_DIR = test/
TEST_OBJS_DIR = $(TESTS_DIR)objs/

TEST_NAME = test_malloc

SRCS = $(SRCS_DIR)malloc.c \
	$(SRCS_DIR)realloc.c \
	$(SRCS_DIR)free.c \
	$(SRCS_DIR)show_alloc_mem.c \
	$(SRCS_DIR)heap.c \
	$(SRCS_DIR)zone.c \
	$(SRCS_DIR)zone_utils.c \
	$(SRCS_DIR)block.c \
	$(SRCS_DIR)utils/ft_putnbr_fd.c \

TEST_SRCS = $(TESTS_DIR)test.c

OBJS = $(patsubst $(SRCS_DIR)%.c,$(OBJS_DIR)%.o,$(SRCS))
TEST_OBJS = $(patsubst $(TESTS_DIR)%.c,$(TEST_OBJS_DIR)%.o,$(TEST_SRCS))

DEPS = $(OBJS:.o=.d)
TEST_DEPS = $(TEST_OBJS:.o=.d)

all: $(NAME) $(LINK)

$(NAME): $(OBJS) $(FT_PRINTF)
	@echo "Linking $@"
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS) $(FT_PRINTF)

$(LINK): $(NAME)
	@ln -sf $(NAME) $(LINK)

test: $(TEST_NAME)

$(TEST_NAME): $(TEST_OBJS) $(OBJS) $(FT_PRINTF)
	@echo "Linking $@"
	@$(CC) $(CFLAGS) -o $@ $(TEST_OBJS) $(OBJS) $(FT_PRINTF)

$(FT_PRINTF):
	@echo "Starting FT_PRINTF compilation"
	@$(MAKE) -s -C $(FT_PRINTF_DIR) CC="$(CC)" FLAGS="$(CFLAGS)"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(@D)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) $(INCLUDES) $(DEPFLAGS) -o $@ -c $<

$(TEST_OBJS_DIR)%.o: $(TESTS_DIR)%.c
	@mkdir -p $(@D)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) $(INCLUDES) $(DEPFLAGS) -o $@ -c $<

clean:
	@$(MAKE) -s -C $(FT_PRINTF_DIR) clean
	@rm -rf $(OBJS_DIR) $(TEST_OBJS_DIR)

fclean: clean
	@$(MAKE) -s -C $(FT_PRINTF_DIR) fclean
	@rm -f $(NAME) $(LINK) $(TEST_NAME)

re: fclean all

.PHONY: all clean fclean re test

-include $(DEPS) $(TEST_DEPS)
