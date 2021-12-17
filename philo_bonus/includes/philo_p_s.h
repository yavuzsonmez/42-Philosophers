/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_p_s.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:02:10 by ysonmez           #+#    #+#             */
/*   Updated: 2021/12/17 17:38:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_P_S_H

# define PHILO_P_S_H


/*	Header and Srcs with Processes and Semaphores */

/*
*	INTEGER
*		MIN : -2147483648
*		MAX : 2147483647
*/

# include	<stdlib.h>
# include	<unistd.h>
# include	<pthread.h>
# include	<stdbool.h>
# include	<semaphore.h>
# include	<stdio.h>
# include	<signal.h>
# include	<fcntl.h>
# include	<sys/time.h>
# include	<sys/stat.h>
# include	<sys/types.h>
# include	<sys/wait.h>

# define EVEN	0
# define ODD	1

typedef struct s_param
{
	int		nb_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		meals_per_philo;
	long	start_time;
}	t_param;

typedef enum e_state
{
	FORK	=	1,
	EAT		=	2,
	SLEEP	=	3,
	THINK	=	4,
	DIE		=	5,
}	t_state;

typedef struct s_ph
{
	t_param			*param;
	sem_t			*sem;
	pid_t			philo;
	long			last_meal;
	int				i;
	int				meal;
}	t_ph;

/*	PHILO.C */
void		schedule(t_ph *ph);

/*	THREADS.C */
t_ph		*create_philo(t_param *param);
int			join_philo(t_ph *ph, int philo);

/*	TIMER.C */
long		get_time(void);
int			ft_sleep(long time, t_ph *ph);

/*	PRINTER.C */
size_t		ft_strlen(const char *s);
int			printer(t_ph *ph, int state);

/*	UTILITIES.C */
long long	ft_atoi_ll(char *str);
int			free_data(t_ph *ph);

#endif
