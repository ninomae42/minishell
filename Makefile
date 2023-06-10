# base dir and target config
NAME := minishell
SRCS_DIR := ./srcs
OBJS_DIR := ./objs

### source files
SRCS := main.c \
		token.c \
		tokenizer.c \
		tokenizer_ctype.c \
		tokenizer_main.c \
		ast.c \
		parser.c \
		parser_main.c \
		parser_utils.c \
		exec_cmd.c \
		exec_main.c \
		exec_args.c \
		exec_path.c \
		err_main.c \
		path_executable.c \
		path_dir_split.c \
		path_utils.c \

SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS := $(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

### include settings
INC_DIR = $(sort $(dir $(SRCS))) $(LIBFT_INC_DIR) $(RL_INC_DIR)
INCLUDES = $(addprefix -I, $(INC_DIR))

### library settings
# libft
LIBFT_DIR := ./libft
LIBFT := ./libft/libft.a
LIBFT_NAME := ft
LIBFT_INC_DIR := ./libft/includes

# readline
RL_DIR := $(shell brew --prefix readline)
RL_NAME := readline
RL_LIB_DIR := $(addprefix $(RL_DIR)/, lib)
RL_INC_DIR := $(addprefix $(RL_DIR)/, lib)

LIBS := $(LIBFT_NAME) $(RL_NAME)

LIB_DIR := $(LIBFT_DIR) $(RL_LIB_DIR)
LIB_DIR := $(addprefix -L, $(LIB_DIR))

LFLAGS := $(addprefix -l, $(LIBS))
LDFLAGS := $(LIB_DIR) $(LFLAGS)

### compiler settings
CC := cc
CFLAGS := -Wall -Wextra -Werror -MMD -MP
# CFLAGS += -g
# CFLAGS += -fsanitize=undefined
# CFLAGS += -fsanitize=address
MAKE := make
RM := rm -rf

.PHONY: all
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

.PHONY: clean
clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(RM) $(OBJS_DIR)

.PHONY: fclean
fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

.PHONY: re
re: fclean all

.PHONY: t
t: all
	python3 ./tests/test.py

.PHONY: norm
norm:
	-@norminette srcs/ | grep -v "INVALID_HEADER"

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

-include $(DEPS)
