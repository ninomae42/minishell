# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/27 17:01:32 by tashimiz          #+#    #+#              #
#    Updated: 2023/05/24 13:02:35 by tashimiz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libft.a

SRCS_DIR := ./srcs
OBJS_DIR := ./objs

SRCS := ft_isalpha.c \
	   ft_isdigit.c \
	   ft_isalnum.c \
	   ft_isascii.c \
	   ft_isprint.c \
	   ft_isupper.c \
	   ft_islower.c \
	   ft_toupper.c \
	   ft_tolower.c \
	   ft_strlen.c \
	   ft_strchr.c \
	   ft_strrchr.c \
	   ft_strncmp.c \
	   ft_strnstr.c \
	   ft_strlcpy.c \
	   ft_strlcat.c \
	   ft_strjoin.c \
	   ft_memset.c \
	   ft_bzero.c \
	   ft_memcpy.c \
	   ft_memmove.c \
	   ft_memchr.c \
	   ft_memcmp.c \
	   ft_calloc.c \
	   ft_strdup.c \
	   ft_atoi.c \
	   ft_substr.c \
	   ft_split.c \
	   ft_strtrim.c \
	   ft_itoa.c \
	   ft_strmapi.c \
	   ft_striteri.c \
	   ft_putchar_fd.c \
	   ft_putstr_fd.c \
	   ft_putendl_fd.c \
	   ft_putnbr_fd.c \
	   ft_lstnew.c \
	   ft_lstadd_front.c \
	   ft_lstsize.c \
	   ft_lstlast.c \
	   ft_lstadd_back.c \
	   ft_lstdelone.c \
	   ft_lstclear.c \
	   ft_lstiter.c \
	   ft_lstmap.c \
	   get_next_line.c \

OBJS := $(SRCS:.c=.o)
SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS := $(addprefix $(OBJS_DIR)/, $(OBJS))


INC_DIR := ./includes
INCLUDES := $(addprefix -I, $(INC_DIR))

DEPENDS := $(OBJS:.o=.d)

CC := cc
CFLAGS := -Wall -Wextra -Werror -MP -MMD

AR := ar
ARFLAGS := rcs
RM := rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

$(OBJS_DIR)/%o: $(SRCS_DIR)/%c
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEPENDS)
