# base dir and target config
NAME := minishell
SRCS_DIR := ./srcs
OBJS_DIR := ./objs

### source files
SRCS := main.c \
		token.c \
		token_utils.c \
		tokenizer.c \
		tokenizer_ctype.c \
		tokenizer_main.c \
		tokenizer_word.c \
		tokenizer_redirect.c \
		tokenizer_pipeline.c \
		ast.c \
		ast_utils.c \
		parser.c \
		parser_main.c \
		parser_simple_command.c \
		parser_utils.c \
		parser_redirect.c \
		expander.c \
		expander_utils.c \
		expander_utils2.c \
		exec_main.c \
		exec_cmd.c \
		exec_dealloc.c \
		exec_binary.c \
		exec_parent.c \
		exec_build.c \
		exec_redirect.c \
		exec_redirect_prepare.c \
		exec_redirect_set.c \
		exec_pipes.c \
		exec_heredoc.c \
		err_main.c \
		err_parser.c \
		err_builtin.c \
		path_dir_split.c \
		path_dir_utils.c \
		path_utils.c \
		ft_strcmp.c \
		ft_strndup.c \
		env_main.c \
		env_add.c \
		env_delete.c \
		env_get.c \
		env_utils.c \
		env_load_environ.c \
		builtin.c \
		builtin_echo.c \
		builtin_cd.c \
		builtin_pwd.c \
		builtin_export.c \
		builtin_export_print.c \
		builtin_unset.c \
		builtin_env.c \
		builtin_exit.c \
		signal.c \

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

# Get target OS name
UNAME := $(shell uname)

# readline
RL_NAME := readline
ifeq ($(UNAME), Darwin)
	RL_DIR := $(shell brew --prefix readline)
	RL_LIB_DIR := $(addprefix $(RL_DIR)/, lib)
	RL_INC_DIR := $(addprefix $(RL_DIR)/, include)
endif

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
