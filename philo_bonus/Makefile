# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: home <home@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/13 11:10:43 by ysonmez           #+#    #+#              #
#    Updated: 2021/12/09 19:18:36 by home             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Reset
Set_Color		=		\033[0m						# Text Reset

# Regular Colors
Black			=		\033[0;30m					# Black
Red				=		\033[0;31m					# Red
Green			=		\033[0;32m					# Green
Yellow			=		\033[0;33m					# Yellow
Blue			=		\033[0;34m					# Blue
Purple			=		\033[0;35m					# Purple
Cyan			=		\033[0;36m					# Cyan
White			=		\033[0;37m					# White

NAME			=		philo

SRCS			=		srcs_thread_mutex/philo.c \
						srcs_thread_mutex/threads.c \
						srcs_thread_mutex/utilities.c \
						srcs_thread_mutex/timer.c \
						srcs_thread_mutex/printer.c \

OBJS			=		$(SRCS:.c=.o)

CFLAGS			=		-Wall -Wextra -Werror -g -fsanitize=thread

$(NAME)			:		$(OBJS)
						@gcc $(CFLAGS) $(OBJS) -lpthread -o $(NAME)
						@echo "$(Cyan)Philosopher with Processes and Semaphores has been created$(Set_Color)"

clean			:
						@rm -f $(OBJS)
						@echo "$(Red).o files have been removed$(Set_Color)"

fclean			:		clean
						@rm -f $(NAME)
						@echo "$(Red)Philo with Processes and Semaphores has been removed$(Set_Color)"

all				:		$(NAME)

re				:		fclean all

bonus			:		all

.PHONY			:		clean fclean all re bonus
