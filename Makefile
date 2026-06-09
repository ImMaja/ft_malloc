NAME = something
COMPILER = cc

COMPILER_FLAGS = -Wall -Wextra -Werror
LIBFT_FLAG = -Llibft -l:libft.a
INCLUDES = -I includes -I libft
DEPFLAGS = -MMD -MP

SRCS_DIR = src/
OBJS_DIR = objs/

SRCS = $(SRCS_DIR)main.c

OBJS = $(patsubst $(SRCS_DIR)%.c,$(OBJS_DIR)%.o,$(SRCS))
DEPS = $(OBJS:.o=.d)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c | $(OBJS_DIR)
	@echo "Compiling $<"
	@$(COMPILER) $(COMPILER_FLAGS) $(INCLUDES) $(DEPFLAGS) -o $@ -c $<

$(NAME) : $(OBJS)
	@echo "Starting LIBFT compilation"
	@make -s -C libft/
	@$(COMPILER) $(COMPILER_FLAGS) -o $@ $(OBJS) $(LIBFT_FLAG)

re : fclean $(NAME)

all : $(NAME)

clean :
	@make -s -C libft/ clean
	@rm -rf $(OBJS_DIR)

fclean : clean
	@make -s -C libft/ fclean
	@rm -rf $(NAME)

gasoil :
	@$(MAKE) -j 32 --no-print-directory

regasoil : fclean
	@$(MAKE) -j 32 --no-print-directory


$(OBJS_DIR) :
	@mkdir -p $(OBJS_DIR)

.PHONY: re all clean fclean gasoil regasoil

-include $(DEPS)