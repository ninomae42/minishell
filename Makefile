# base dir and target config
NAME := minishell
SRCS_DIR := ./srcs
OBJS_DIR := ./objs

# main file
MAIN_SRC := main.c
MAIN_SRC := $(addprefix $(SRCS_DIR)/, $(MAIN_SRC))

# parser files
# PARSER_DIR := parser
# PARSER_SRCS := parser.c
#
# PARSER_DIR := $(addprefix $(SRCS_DIR)/, $(PARSER_DIR))
# PARSER_SRCS := $(addprefix $(PARSER_DIR)/, $(PARSER_SRCS))

# tokenizer files
TOKENIZER_DIR := tokenizer
TOKENIZER_SRCS := tokenizer.c \
				  tokenizer_helper.c \
				  tokenizer_utils.c \
				  utils.c \

TOKENIZER_DIR := $(addprefix $(SRCS_DIR)/, $(TOKENIZER_DIR))
TOKENIZER_SRCS := $(addprefix $(TOKENIZER_DIR)/, $(TOKENIZER_SRCS))

# all source and object deps files
SRCS := $(MAIN_SRC) $(TOKENIZER_SRCS) $(PARSER_SRCS)
OBJS := $(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

# include settings
INC_DIR := $(sort $(dir $(SRCS)))
INCLUDES := $(addprefix -I, $(INC_DIR))

# library setting
LIBS :=
LIB_DIR :=
LFLAGS := $(addprefix -l, $(LIBS))
LDFLAGS := $(LIB_DIR) $(LFLAGS)

# compiler settings
CC := cc
CFLAGS := -Wall -Wextra -Werror -MMD -MP
# CLFAGS += -g
# CLFAGS += -fsanitize=undefined
# CLFAGS += -fsanitize=address
RM := rm -rf

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

.PHONY: clean
clean:
	$(RM) $(OBJS_DIR)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all

-include $(DEPS)
