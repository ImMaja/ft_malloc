ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

PROJECT_DIR = ..
PROJECT_LIB_NAME = libft_malloc_$(HOSTTYPE).so
PROJECT_LIB = $(PROJECT_DIR)/$(PROJECT_LIB_NAME)
PROJECT_INPUTS = $(PROJECT_DIR)/Makefile \
	$(wildcard $(PROJECT_DIR)/include/*.h) \
	$(wildcard $(PROJECT_DIR)/src/*.c) \
	$(wildcard $(PROJECT_DIR)/src/*/*.c)

CC = cc
CFLAGS = -Wall -Wextra -Werror \
	-pthread \
	-fno-builtin-malloc \
	-fno-builtin-calloc \
	-fno-builtin-realloc \
	-fno-builtin-free
DEPFLAGS = -MMD -MP
INCLUDES = -I $(PROJECT_DIR)/include
RPATH = -Wl,-rpath,'$$ORIGIN/../../..'

BUILD_DIR = .build
OBJS_DIR = $(BUILD_DIR)/objs
BIN_DIR = $(BUILD_DIR)/bin

TEST_NAME = $(BIN_DIR)/test_malloc
SHOW_TEST_NAME = $(BIN_DIR)/test_show_alloc_mem
PRELOAD_TEST_NAME = $(BIN_DIR)/test_preload

TEST_SRCS = test.c \
	test_utils.c \
	test_malloc.c \
	test_free.c \
	test_realloc.c \
	test_stress.c \
	test_thread.c
SHOW_TEST_SRCS = test_show_alloc_mem.c
PRELOAD_TEST_SRCS = test_preload.c

TEST_OBJS = $(patsubst %.c,$(OBJS_DIR)/%.o,$(TEST_SRCS))
SHOW_TEST_OBJS = $(patsubst %.c,$(OBJS_DIR)/%.o,$(SHOW_TEST_SRCS))
PRELOAD_TEST_OBJS = $(patsubst %.c,$(OBJS_DIR)/%.o,$(PRELOAD_TEST_SRCS))
DEPS = $(TEST_OBJS:.o=.d) $(SHOW_TEST_OBJS:.o=.d) \
	$(PRELOAD_TEST_OBJS:.o=.d)

all: $(TEST_NAME) $(SHOW_TEST_NAME) $(PRELOAD_TEST_NAME)

test: $(TEST_NAME)

check: $(TEST_NAME) $(PRELOAD_TEST_NAME)
	@$(TEST_NAME)
	@LD_PRELOAD="$(abspath $(PROJECT_LIB))" $(PRELOAD_TEST_NAME)

test-show: $(SHOW_TEST_NAME)
	@$(SHOW_TEST_NAME)

test-preload: $(PRELOAD_TEST_NAME) $(PROJECT_LIB)
	@LD_PRELOAD="$(abspath $(PROJECT_LIB))" $(PRELOAD_TEST_NAME)

test-valgrind: $(TEST_NAME)
	@valgrind --tool=memcheck --error-exitcode=99 --leak-check=full \
		--track-origins=yes --show-leak-kinds=all \
		--soname-synonyms=somalloc=nouserintercepts $(TEST_NAME)

$(PROJECT_LIB): $(PROJECT_INPUTS)
	@$(MAKE) -C $(PROJECT_DIR) all

$(TEST_NAME): $(TEST_OBJS) $(PROJECT_LIB)
	@mkdir -p $(@D)
	@echo "Linking $@"
	@$(CC) $(CFLAGS) -o $@ $(TEST_OBJS) -L$(PROJECT_DIR) $(RPATH) \
		-Wl,--no-as-needed -l:$(PROJECT_LIB_NAME)

$(SHOW_TEST_NAME): $(SHOW_TEST_OBJS) $(PROJECT_LIB)
	@mkdir -p $(@D)
	@echo "Linking $@"
	@$(CC) $(CFLAGS) -o $@ $(SHOW_TEST_OBJS) -L$(PROJECT_DIR) $(RPATH) \
		-Wl,--no-as-needed -l:$(PROJECT_LIB_NAME)

$(PRELOAD_TEST_NAME): $(PRELOAD_TEST_OBJS)
	@mkdir -p $(@D)
	@echo "Linking $@"
	@$(CC) $(CFLAGS) -o $@ $(PRELOAD_TEST_OBJS) -ldl

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) $(INCLUDES) $(DEPFLAGS) -o $@ -c $<

clean:
	@rm -rf $(BUILD_DIR)

fclean: clean

re: fclean all

.PHONY: all test check test-show test-preload test-valgrind clean fclean re

-include $(DEPS)
