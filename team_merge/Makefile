# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jihyeki2 <jihyeki2@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/17 13:01:11 by jihyeki2          #+#    #+#              #
#    Updated: 2025/03/18 01:34:06 by jihyeki2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAG = -g -Wall -Wextra -Werror
LDFLAG = -lreadline -lncurses
LIBS = -Llibft -lft

SRC = main.c main_utils.c\
	src/parsing/error.c src/parsing/init.c src/parsing/add_list_node.c src/parsing/tokenizer.c\
	src/parsing/tokenizer_read.c src/parsing/utils.c src/parsing/env_parse.c src/parsing/merge_token.c\
	src/parsing/expand_env.c src/parsing/free.c src/parsing/compare_env_key.c src/parsing/debug.c\
	src/parsing/syntax_check.c src/parsing/transfer_env.c\
	src/parsing/change_struct_parser.c src/parsing/parser_utils.c src/parsing/parser_init.c\
	src/builtins/ft_cd.c src/builtins/ft_echo.c src/builtins/ft_env.c src/builtins/ft_export.c\
	src/builtins/ft_pwd.c src/builtins/ft_unset.c src/builtins/ft_exit.c src/builtins/built_utils.c\
	src/redir/redirec_main.c src/redir/redir_utils.c src/redir/redir_utils2.c src/redir/redir_utils3.c src/redir/redir_utils4.c\
	src/redir/expand_hd.c src/parsing/env_utils.c\
	src/parsing/parsing_utils.c src/parsing/parsing_utils3.c\
	src/execute/execute.c src/execute/execute_utils.c\
	src/pipe/pipe_utils.c src/pipe/pipe_utils2.c src/pipe/pipe_main.c\
	src/signals/signal_main.c src/parsing/expands_utils.c src/parsing/expands.c src/parsing/parsing_utils.c src/parsing/parsing_utils3.c\
	get_next_line/get_next_line.c get_next_line/get_next_line_utils.c\

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME): $(OBJ) libft/libft.a
	@echo "\033[0;33m\nMaking[...]\n\n" 
	@$(CC) $(CFLAG) -o $@ $^ $(LIBS) $(LDFLAG)
	@echo "\033[0;32m\nREADY TO EXECUTE!\n"
	@echo "\033[0;90m\n...created by chanypar and jihyeki2\n"

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

#src/parsing/parsing_utils.c src/parsing/parsing_utils2.c\