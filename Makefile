# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgenie <bgenie@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/02 17:55:36 by bgenie            #+#    #+#              #
#    Updated: 2022/09/02 18:00:21 by bgenie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CFLAGS = -Wall -Werror -Wextra

SRCS =	philo.c \
		init.c \
		simulation.c \
		utils.c

OBJS = ${SRCS:.c=.o}

INCLUDES = -I./

NAME = philo

all:		${OBJS}
	${CC} ${CFLAGS} ${INCLUDES} -o ${NAME} ${OBJS}

${NAME}:	all

clean:
	rm -f ${OBJS}

fclean:		clean
	rm -f ${NAME}

re:			fclean all

.PHONY: all clean fclean re