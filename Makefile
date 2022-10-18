# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgenie <bgenie@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/02 17:55:36 by bgenie            #+#    #+#              #
#    Updated: 2022/09/11 17:54:08 by bgenie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CFLAGS = -Wall -Werror -Wextra

SRCS =	philo.c \
		init.c \
		simulation.c \
		utils.c \
		free.c

OBJS = ${SRCS:.c=.o}

INCLUDES = -I./

DEBUG = -g -fsanitize=address

LEAKS = -Ileaks_checker/includes -Lleaks_checker -lleaks

NAME = philo

all:		${OBJS}
	${CC} ${CFLAGS} ${INCLUDES} -o ${NAME} ${OBJS}

${NAME}:	all

test:		${OBJS}
	${CC} ${CFLAGS} ${DEBUG} ${INCLUDES} -o ${NAME} ${OBJS}

leaks:		${OBJS}
	${CC} ${CFLAGS} ${DEBUG} ${INCLUDES} ${LEAKS} -o ${NAME} ${OBJS}

clean:
	rm -f ${OBJS}

fclean:		clean
	rm -f ${NAME}

re:			fclean all

.PHONY: all clean fclean re