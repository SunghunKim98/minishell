# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: soahn <soahn@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/21 00:17:03 by soahn             #+#    #+#              #
#    Updated: 2022/05/30 19:46:43 by soahn            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra

LDFLAGS = -L${HOME}/.brew/opt/readline/lib
CPPFLAGS= -I${HOME}/.brew/opt/readline/include

AR 		= ar rcs
RM		= rm -f

INCS_DIR		= ./include/
SRCS_DIR		= ./src/
LIB_DIR			= ./lib/
LIB_NAME		= ./lib/libft.a

SRC		=	main.c builtin/builtin_helper.c builtin/builtin.c builtin/cd.c builtin/echo.c builtin/env.c builtin/exit.c builtin/export.c builtin/pwd.c builtin/unset.c\
			execute/execute_helper.c execute/execute.c execute/handler.c execute/heredoc.c execute/pipe.c execute/process.c execute/redirection.c \
			init/init.c init/setting_env.c utility/utils.c \
			error/errorcheck.c error/error.c check/check_case.c \
			makeline/command_line.c makeline/line_init.c makeline/line_parse_1.c \
			makeline/line_parse_2.c makeline/line_parse_3.c makeline/line_parse_4.c \
			makeline/pipe_parse.c utility/advanced_utils.c utility/free_utils.c \
			utility/malloc_utils.c utility/set_utils.c utility/set_utils_2.c utility/error_utils.c \
			utility/env_utils.c\


SRCS	= $(addprefix $(SRCS_DIR), $(SRC))
OBJS	= $(SRCS:.c=.o)

$(NAME) : $(OBJS)
	make -C $(LIB_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB_NAME) -lreadline ${LDFLAGS} ${CPPFLAGS}

all : $(NAME)

clean :
	make -C $(LIB_DIR) clean
	$(RM) $(OBJS)

fclean : clean
	make -C $(LIB_DIR) fclean
	$(RM) $(NAME)

re : fclean all

PHONY : all clean fclean re
