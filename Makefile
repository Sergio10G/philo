# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdiez-ga <sdiez-ga@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 16:28:33 by sdiez-ga          #+#    #+#              #
#    Updated: 2023/03/06 19:15:42 by sdiez-ga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

SRC			=	./philo.c						\
				./init_structs.c				\
				./input_parse.c					\
				./utils.c						\
				./utils_2.c						\
				./free_funcs.c					\
				./thread_funcs.c				\
				./thread_funcs_2.c				\
				./control_funcs.c

OBJS		=	${SRC:.c=.o}

CC			=	gcc

CFLAGS		=	-Wall -Werror -Wextra

RM			=	rm -f

GREEN		=	\033[1;32m
PINK		=	\033[1;35m
PINK_BG		=	\033[7;35m
BLUE		=	\033[1;36m
RESET		=	\033[1;0m
GRAY		=	\033[2;37m

%.o			:	%.c
				@printf "$(GRAY)"
				$(CC) $(CFLAGS) -c $< -o $@
				@printf "$(RESET)"

$(NAME)		:	$(OBJS)
				@printf "$(GRAY)"
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
				@printf "$(RESET)"
				@echo "$(PINK_BG)Philosophers compiled!$(RESET)"

all			:	$(NAME)

clean		:
				@printf "$(GRAY)"
				$(RM) $(OBJS)
				@printf "$(RESET)"
				@echo "$(PINK)Philosophers objs cleaned!$(RESET)"

fclean		:	clean
				@printf "$(GRAY)"
				$(RM) $(NAME)
				@printf "$(RESET)"
				@echo "$(PINK)Philosophers binary deleted!$(RESET)"

re			:	fclean all

.PHONY		:	all clean fclean re
