NAME        := minishell
CC        := clang

FLAGS    := -Wall -Wextra -Werror -fcommon -g
LIBFT	 := libft/libft.a
#FLAGS       := -fsanitize=address -g
# FLAGS := -g
SRCS        :=         	  main.c \
                          parser.c \
                          parser1.c \
                          parsepushback.c \
                          mutiple_command.c \
                          linked_list.c \
                          lexer.c \
                          initbuiltin.c \
                          free.c \
                          expand3.c \
                          expand2.c \
                          expand1.c \
						  expand.c  \
                          executer.c \
                          error.c \
                          new_bul/ft_cd.c \
                          new_bul/ft_cd1.c \
                          new_bul/ft_echo.c \
                          new_bul/ft_unset.c \
                          new_bul/ft_env.c \
                          new_bul/ft_exit.c \
                          new_bul/ft_export_utils.c \
                          new_bul/ft_export.c \
                          new_bul/ft_pwd.c \
                          executer/executer1.c \
                          executer/executer2.c \
                          executer/executer3.c \
                          executer/executer4.c \
                          executer/pipes.c \
						  split_token.c \
						  split_token2.c \
						  split_token3.c \
                          
OBJS        := $(SRCS:.c=.o)

.c.o:
	@${CC} ${FLAGS} -c $< -o ${<:.c=.o} -I/Users/ohayek/readline/include

RM		    := rm -f

${NAME}:	${LIBFT} ${OBJS}
			@echo "[COMPILING...]"
			@${CC} ${FLAGS} -o ${NAME} ${OBJS} ${LIBFT} -I/Users/ohayek/readline/include -L/Users/ohayek/readline/lib -lreadline
			@echo "[COMPILING FINISHED]"
${LIBFT}:
	make -C libft/

all:		${NAME}

bonus:		all

clean:
			@echo "[DELETING...]"
			@${RM} *.o */*.o */*/*.o
			@echo "[DELETED]"

fclean:		clean
			@${RM} ${NAME}
			make -C libft/ fclean

re:			fclean all

.PHONY:		all clean fclean re
