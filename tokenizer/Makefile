NAME := tokenizer

SRCS_DIR := ./
OBJS_DIR := ./objs

SRCS := main.c \

OBJS := $(SRCS:.c=.o)
SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS := $(addprefix $(OBJS_DIR)/, $(OBJS))

INC_DIR := ./
INCLUDES := $(addprefix -I, $(INC_DIR))

# LIBS := 
# LFLAGS := $(addprefix -l, $(LIBS))

CC := cc
CFLAGS := -Wall -Wextra -Werror
# CFLAGS += -g
# CFLAGS += -fsanitize=undefined
# CFLAGS += -fsanitize=address
# CFLAGS += -fsanitize=thread
RM := rm -rf

.PHONY: all
all: $(NAME)

$(OBJS_DIR)/%o: $(SRCS_DIR)/%c
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

# $(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

.PHONY: clean
clean:
	$(RM) $(OBJS_DIR)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all

.PHONY: t
t: all
	python3 test.py

.PHONY: norm
norm:
	-@norminette ./ | grep -v "INVALID_HEADER"
