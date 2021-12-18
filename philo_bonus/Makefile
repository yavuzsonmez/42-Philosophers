# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: node <node@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/13 11:10:43 by ysonmez           #+#    #+#              #
#    Updated: 2021/12/18 14:19:41 by node             ###   ########.fr        #
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

SRCS			=		srcs_process_semaphore/main.c \
						srcs_process_semaphore/diner.c \
						srcs_process_semaphore/processes.c \
						srcs_process_semaphore/timer.c \
						srcs_process_semaphore/printer.c \
						srcs_process_semaphore/utilities.c \

OBJS			=		$(SRCS:.c=.o)

CFLAGS			=		-Wall -Wextra -Werror

$(NAME)			:		$(OBJS)
						@gcc $(CFLAGS) $(OBJS) -pthread -o $(NAME)
						@echo "$(Cyan)Philo with Processes and Semaphores has been created$(Set_Color)"

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
