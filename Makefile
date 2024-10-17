NAME = minishell
CC = cc
CFLAG = -g 
LDFLAG = -lreadline -lncurses
LIBS = -Llibft -lft

SRC = src/parsing/env.c src/parsing/expands.c src/parsing/expands_utils.c src/parsing/utils.c src/parsing/lexing.c\
	src/parsing/split_request.c src/parsing/syntax.c src/parsing/post_parsing.c src/parsing/automate.c src/parsing/all_toge.c\
	src/builtins/ft_cd.c src/builtins/ft_echo.c src/builtins/ft_env.c src/builtins/ft_export.c\
	src/builtins/ft_pwd.c src/builtins/ft_unset.c src/builtins/ft_exit.c src/builtins/built_utils.c\
	src/redir/redirec_main.c src/redir/redir_utils.c src/redir/redir_utils2.c src/redir/expand_hd.c\
	src/main.c src/main_utils.c src/execute/execute.c src/execute/execute_utils.c\
	src/pipe/pipe_utils.c src/pipe/pipe_main.c src/parsing/pro_pars.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME): $(OBJ) libft/libft.a
	@echo "\033[0;33m\nMaking[...]\n\n" 
	@$(CC) $(CFLAG) -o $@ $^ $(LIBS) $(LDFLAG)
	@echo "\033[0;32m\nREADY TO EXECUTE!\n"
	@echo "\033[0;90m\n...created by chanypar & ihibti\n"

libft/libft.a:
	@make -C libft

%.o: %.c
	@$(CC) $(CFLAG) -o $@ -c $<

clean :
	@echo "\033[0;31m\nObjects files will be destroyed[...]\n"
	@rm -f $(OBJ)
	@make -C libft clean
	@echo "\033[0;32m\nDONE!\n"

fclean : clean
	@echo "\033[0;31m\nExecutes files will be destroyed[...]\n"
	@rm -f $(NAME)
	@make -C libft fclean
	@echo "\033[0;32m\nDONE!\n"

re : fclean all

.PHONY: all clean fclean re
