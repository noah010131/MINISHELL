# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jihyeki2 <jihyeki2@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/12 10:10:16 by princessj         #+#    #+#              #
#    Updated: 2025/03/14 20:25:25 by jihyeki2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

SRC_DIR			=	./src/
INC_DIR			=	./include/

MAIN			=	main.c

SRCS			=	error.c \
					init.c \
					add_list_node.c \
					tokenizer.c \
					tokenizer_read.c \
					utils.c \
					env_parse.c \
					merge_token.c \
					expand_env.c \
					free.c \
					compare_env_key.c \
					debug.c	\


SRC				=	$(addprefix $(SRC_DIR), $(SRCS))
SRC_MAIN		=	$(addprefix $(SRC_DIR), $(MAIN))

OBJS			=	${SRC:.c=.o}
OBJ_MAIN		=	${SRC_MAIN:.c=.o}

LD_FLAGS        =   -L libft

HEAD			=	-I include -I libft

CC				=  	gcc
CFLAGS			=	-Wall -Werror -Wextra -g3
LIBS			=	-lreadline

.c.o:
	${CC} ${CFLAGS} ${HEAD} -c $< -o $@

$(NAME)			:	${OBJS} ${OBJ_MAIN}
	@make -C libft
	@${CC} ${CFLAGS} ${LD_FLAGS} ${OBJ_MAIN} ${OBJS} -o ${NAME} -lft -lreadline

all				:	${NAME}

clean 			:
	@make clean -C libft
	@rm -rf ${OBJS} ${OBJ_MAIN}

fclean			:	clean
	@make fclean -C libft
	@rm -rf ${NAME}

re				:	fclean all

.PHONY			:	all clean fclean re

#-fsanitize=address
#CC = clang