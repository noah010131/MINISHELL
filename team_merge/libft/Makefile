# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jihyeki2 <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/03 18:10:02 by jihyeki2          #+#    #+#              #
#    Updated: 2024/09/19 18:28:09 by jihyeki2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC	= ft_memset ft_bzero ft_memchr ft_memcmp ft_strlen ft_isalpha \
	  ft_isdigit ft_isalnum ft_isascii ft_isprint ft_toupper ft_tolower \
	  ft_strchr ft_strrchr ft_strncmp ft_strlcpy ft_strlcat ft_strnstr \
	  ft_atoi ft_strdup ft_calloc ft_substr ft_strjoin ft_strtrim \
	  ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd ft_strmapi \
	  ft_striteri ft_split ft_itoa ft_memcpy ft_memmove \
	  get_next_line_bonus get_next_line_utils_bonus \
	  ft_printf ft_format \

SRCS	= $(addsuffix .c, ${SRC})

HEAD	= ./includes/ 

OBJS	= ${SRCS:.c=.o}

B_OBJS	= ${B_SRCS:.c=.o}

NAME	= libft.a

CC	= gcc
RM	= rm -f
AR	= ar rc

CFLAGS	= -Wall -Wextra -Werror

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
	${AR} ${NAME} ${OBJS}

all:	$(NAME)

clean:
	${RM} ${OBJS} ${B_OBJS}

fclean:	clean
	${RM} $(NAME)

re:	fclean all

.PHONY:	all bonus clean fclean re
