NAME	= test

CC		= gcc 
# todo: gcc 말고 cc로 컴파일하라는 소리 있던데..? 확인 필요
# todo: libft 컴파일 추가
CFLAGS	= -Wall -Werror -Wextra

# cluster
# LDFLAGS = -L${HOME}/.brew/opt/readline/lib
# CPPFLAGS= -I${HOME}/.brew/opt/readline/include

# soahn home
LDFLAGS = -L/usr/local/opt/readline/lib
CPPFLAGS= -I/usr/local/opt/readline/include

AR 		= ar rcs
RM		= rm -f

INCS_DIR		= ./include/
SRCS_DIR		= ./src/
LIB_DIR			= ./lib/
LIB_NAME		= ./lib/libft.a

SRCS		= env.c

# SRCS	= $(addprefix $(SRCS_DIR), $(SRC))
OBJS	= $(SRCS:.c=.o)

$(NAME) : $(OBJS)
#	make -C $(LIB_DIR)
#todo: 제출 전에 라이브러리 컴파일 하도록 수정
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB_NAME) -lreadline ${LDFLAGS} ${CPPFLAGS}

all : $(NAME)

clean :
	make -C $(LIB_DIR) clean
	$(RM) $(OBJS)

fclean : clean
#	make -C $(LIB_DIR) fclean
#todo 제출 전에 주석 삭제!
	$(RM) $(NAME)

re : fclean all

PHONY : all clean fclean re