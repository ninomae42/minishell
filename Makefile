# base dir and target config
NAME := minishell
SRCS_DIR := ./srcs
OBJS_DIR := ./objs

# main file
MAIN_SRC := main.c
MAIN_SRC := $(addprefix $(SRCS_DIR)/, $(MAIN_SRC))

# utils files
UTILS_DIR := utils
UTILS_SRCS := perror_exit.c

UTILS_DIR := $(addprefix $(SRCS_DIR)/, $(UTILS_DIR))
UTILS_SRCS := $(addprefix $(UTILS_DIR)/, $(UTILS_SRCS))

# environment files
ENV_DIR := environ
ENV_SRCS := load_env.c \
			env_init.c \
			env_utils.c \
			ft_getenv.c \
			ft_setenv.c \
			ft_unsetenv.c \
			ft_printenv.c \

ENV_DIR := $(addprefix $(SRCS_DIR)/, $(ENV_DIR))
ENV_SRCS := $(addprefix $(ENV_DIR)/, $(ENV_SRCS))

# executor files
EXEC_DIR := exec
EXEC_SRCS := exec.c

EXEC_DIR := $(addprefix $(SRCS_DIR)/, $(EXEC_DIR))
EXEC_SRCS := $(addprefix $(EXEC_DIR)/, $(EXEC_SRCS))

# parser files
PARSER_DIR := parser
PARSER_SRCS := parser.c

PARSER_DIR := $(addprefix $(SRCS_DIR)/, $(PARSER_DIR))
PARSER_SRCS := $(addprefix $(PARSER_DIR)/, $(PARSER_SRCS))

# tokenizer files
TOKENIZER_DIR := tokenizer
TOKENIZER_SRCS := tokenizer.c \
				  tokenizer_helper.c \
				  tokenizer_utils.c \

TOKENIZER_DIR := $(addprefix $(SRCS_DIR)/, $(TOKENIZER_DIR))
TOKENIZER_SRCS := $(addprefix $(TOKENIZER_DIR)/, $(TOKENIZER_SRCS))

# all source and object deps files
SRCS := $(MAIN_SRC) $(TOKENIZER_SRCS) $(PARSER_SRCS) $(EXEC_SRCS) $(ENV_SRCS) $(UTILS_SRCS)
OBJS := $(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

# include settings
INC_DIR = $(sort $(dir $(SRCS))) $(LIBFT_INC_DIR)
INCLUDES = $(addprefix -I, $(INC_DIR))

# library setting
# libft
LIBFT_DIR := ./libft
LIBFT := ./libft/libft.a
LIBFT_LIB_NAME := ft
LIBFT_INC_DIR := ./libft/includes
#
LIBS := $(LIBFT_LIB_NAME)

LIB_DIR := $(LIBFT_DIR)
LIB_DIR := $(addprefix -L, $(LIB_DIR))

LFLAGS := $(addprefix -l, $(LIBS))
LDFLAGS := $(LIB_DIR) $(LFLAGS)

# compiler settings
CC := cc
CFLAGS := -Wall -Wextra -Werror -MMD -MP
# CFLAGS += -g
# CFLAGS += -fsanitize=undefined
# CFLAGS += -fsanitize=address
MAKE := make
RM := rm -rf

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
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
	python3 ./srcs/parser/test.py


$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

-include $(DEPS)
