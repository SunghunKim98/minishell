# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: soahn <soahn@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/19 15:58:12 by sashin            #+#    #+#              #
#    Updated: 2022/05/08 00:00:00 by soahn            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Original version created by sashin from 42 Seoul
# If you want to add library, add "$(SRC)", "$(SRC_DIR)", dependancy of $(NAME) and clean

NAME			= libft.a

CC				= gcc
CFLAGS			= -Wall -Werror -Wextra

AR				= ar
ARFLAGS			= -rcs

INCLUDES_DIR	= include
LIBFT_DIR		= src/libft

LIBFT			= ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
				ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c \
				ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c \
				ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
				ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c ft_substr.c \
				ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
				ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
				ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
				ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_swap_int.c \
				ft_num_tobase.c

all: $(NAME)

$(NAME): libft

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $^
	@$(AR) $(ARFLAGS) $(NAME) $@

libft: $(addprefix $(LIBFT_DIR)/, $(LIBFT:.c=.o))

clean:
	rm -rf $(addprefix $(LIBFT_DIR)/, $(LIBFT:.c=.o))

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re libft
