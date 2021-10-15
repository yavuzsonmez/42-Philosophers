# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/13 11:10:43 by ysonmez           #+#    #+#              #
#    Updated: 2021/10/15 18:43:25 by ysonmez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=		philo

SRCS			=		srcs/philo.c \

OBJS			=		$(SRCS:.c=.o)

OBJS_CHECKER	=		$(SRCS_CHECKER:.c=.o)

CC				=		gcc

CFLAGS			=		-Wall -Wextra -Werror

RM				=		rm -f

$(NAME)			:		$(OBJS)
						$(CC) $(CFLAGS) $(OBJS) -o $(NAME)


clean			:
						$(RM) $(OBJS)
						$(RM) $(OBJS_CHECKER)

fclean			:		clean
						$(RM) $(NAME)

all				:		$(NAME)

re				:		fclean all

bonus			:		all

.PHONY			:		clean fclean all re bonus
