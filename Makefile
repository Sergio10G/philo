# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdiez-ga <sdiez-ga@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 16:28:33 by sdiez-ga          #+#    #+#              #
#    Updated: 2022/11/08 18:00:28 by sdiez-ga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

SRC			=	./philo.c

OBJS		=	${SRC:.c=.o}

CC			=	gcc

CFLAGS		=	-Wall -Werror -Wextra -fsanitize=address

RM			=	rm -f

GREEN		=	\033[1;32m
PINK		=	\033[1;35m
BLUE		=	\033[1;36m
RESET		=	\033[1;0m

MAKEFLAGS	+=	--silent

%.o			:	%.c
				$(CC) $(CFLAGS) -c $< -o $@

$(NAME)		:	$(OBJS)

all			:	$(NAME)

re			:	fclean all

clean		:

fclean		:


.PHONY		:	all clean fclean re
