# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/13 11:10:43 by ysonmez           #+#    #+#              #
#    Updated: 2021/11/02 13:03:38 by ysonmez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=		philo

SRCS			=		srcs_thread_mutex/philo.c \
						srcs_thread_mutex/threads.c \
						srcs_thread_mutex/utilities.c \
						srcs_thread_mutex/timer.c \
						srcs_thread_mutex/printer.c \
						srcs_thread_mutex/ft_itoa.c \

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
