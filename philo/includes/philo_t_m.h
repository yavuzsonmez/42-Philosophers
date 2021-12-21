/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_t_m.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: node <node@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 18:44:16 by ysonmez           #+#    #+#             */
/*   Updated: 2021/12/21 11:24:13 by node             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_T_M_H

# define PHILO_T_M_H

/*	Philosopher with Threads and Mutexes */

/*
*	INTEGER
*		MIN : -2147483648
*		MAX : 2147483647
*/

# include	<stdlib.h>
# include	<unistd.h>
# include	<sys/time.h>
# include	<pthread.h>
# include	<stdbool.h>

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
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*print;
	pthread_mutex_t	*end;
	pthread_t		philosoph;
	long			last_meal;
	int				i;
	int				meal;
	bool			*alive;
}	t_ph;

/*	DINER.C */
void		*schedule(void *ph);

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
