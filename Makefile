NAME = minishell

SRC =	Excution/errors.c \
		Pasring/main.c\
		Pasring/parse.c\
		Pasring/expand.c\
		Pasring/fill_shell.c\
		Pasring/parse_qoutes.c\
		Pasring/node_utils.c\
		Pasring/node_utils_2.c\
		Pasring/parsing_tool.c\
		Pasring/parsing_tool_2.c\
		Pasring/redirection.c\
		Pasring/expand_tool.c\
		Pasring/parsing_tool_3.c\
		lexer/lexer_check.c\
		lexer/lexer_init.c \
		lexer/lexer_utils.c\
		lexer/lexer_utiles_2.c\
		Excution/minishell.c \
		Bultuin/pwd.c\
		Bultuin/cd.c\
		Excution/linked.c\
		Bultuin/unset.c\
		Bultuin/export.c\
		Bultuin/cmd_env.c\
		Excution/excution_utils.c\
		Excution/cmd_excution.c\
		Excution/excution_util.c\
		Excution/her_doc.c\
		Excution/execute_tool.c\
		Excution/minishell_util.c\
		Bultuin/exit.c\
		Bultuin/echo.c\
		Bultuin/bultuin_util.c\
		Excution/heredoc_tool.c\

RM		= rm -rf

CC		= cc

CFLAGS = -Wall -Werror -Wextra
OBJ	= ${SRC:.c=.o}

all	: ${NAME}

${NAME} : ${OBJ}
		make -C libft/
	${CC} ${CFLAGS} ${OBJ} libft/libft.a -o ${NAME} -lreadline -I/Users/${USER}/Desktop/readline/include/ -L /Users/${USER}/Desktop/readline -lcurses
clean :
	make clean -C libft
	$(RM) $(OBJ) 
	
fclean	:	clean
		make fclean -C  libft
		$(RM) $(NAME)

re	:	fclean all