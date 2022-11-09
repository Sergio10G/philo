# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdiez-ga <sdiez-ga@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 16:28:33 by sdiez-ga          #+#    #+#              #
#    Updated: 2022/11/09 19:59:55 by sdiez-ga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

SRC			=	./philo.c						\
				./init_structs.c				\
				./input_parse.c					\
				./utils.c						\
				./print_funcs.c

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
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
				@echo "$(PINK)Philosophers compiled!$(RESET)"

all			:	$(NAME)

clean		:
				$(RM) $(OBJS)
				@echo "$(PINK)Philosophers objs cleaned!$(RESET)"

fclean		:	clean
				$(RM) $(NAME)
				@echo "$(PINK)Philosophers binary deleted!$(RESET)"

re			:	fclean all

.PHONY		:	all clean fclean re
