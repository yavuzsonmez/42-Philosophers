# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/13 11:10:43 by ysonmez           #+#    #+#              #
#    Updated: 2021/11/02 10:14:16 by ysonmez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=		philo

SRCS			=		srcs/philo.c \
						srcs/utilities.c \
						srcs/timer.c \
						srcs/printer.c \
						srcs/ft_itoa.c \

OBJS			=		$(SRCS:.c=.o)

CC				=		gcc

CFLAGS			=		-Wall -Wextra -Werror

RM				=		rm -f

$(NAME)			:		$(OBJS)
						$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean			:
						$(RM) $(OBJS)

fclean			:		clean
						$(RM) $(NAME)

all				:		$(NAME)

re				:		fclean all

bonus			:		all

.PHONY			:		clean fclean all re bonus
