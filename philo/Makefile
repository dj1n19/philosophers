# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgenie <bgenie@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/02 17:55:36 by bgenie            #+#    #+#              #
#    Updated: 2022/11/29 17:19:26 by bgenie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CFLAGS = -Wall -Werror -Wextra

SRCS =	philo.c \
		init.c \
		simulation.c \
		utils.c \
		free.c \
		ft_itoa.c

OBJS = ${SRCS:.c=.o}

INCLUDES = -I./

DEBUG = -fsanitize=address -g

LEAKS_DIR = leaks_checker

LEAKS = -I${LEAKS_DIR} -L${LEAKS_DIR} -lleaks

NAME = philo

.c.o:
	@${CC} ${CFLAGS} -c ${INCLUDE} $< -o ${<:.c=.o}
	@printf "\e[34mCompiling %-40s \e[32m[🐫]\e[0m\n" $<

all:		${OBJS}
	@${CC} ${CFLAGS} ${INCLUDES} -o ${NAME} ${OBJS}
	@printf "\e[36mCompilation of %-35s \e[32m[🐫]\e[0m\n" ${NAME}

${NAME}:	all

test:		${OBJS}
	@${CC} ${CFLAGS} ${DEBUG} ${INCLUDES} -o ${NAME} ${OBJS}
	@printf "\e[36mCompilation of %s with debug %-18s \e[32m[🐫]\e[0m\n" ${NAME} ""

leaks:	leaks_checker ${OBJS}
	@make -C ${LEAKS_DIR}
	@${CC} ${CFLAGS} ${INCLUDES} ${LEAKS} -o ${NAME} ${OBJS}
	@printf "\e[36mCompilation of %s with leaks checker %-10s \e[32m[🐫]\e[0m\n" ${NAME} ""

clean:
	@rm -f ${OBJS}
	@printf "\e[33mRemoving object files...\e[0m\n"

fclean:		clean
	@rm -f ${NAME}
	@printf "\e[33mRemoving binary files...\e[0m\n"

re:			fclean all

.PHONY: all clean fclean re