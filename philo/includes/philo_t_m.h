/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_t_m.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 18:44:16 by ysonmez           #+#    #+#             */
/*   Updated: 2021/12/08 21:04:57 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_T_M_H

# define PHILO_T_M_H

/*	Header and Srcs with _T_M because :
*		Philosopher with Thread and Mutexes
*/

/*
*	INTEGER
*		MIN : -2147483648
*		MAX : 2147483647
*/

# include	<limits.h>
# include	<stdio.h>
# include	<string.h>
# include	<stdlib.h>
# include	<unistd.h>
# include	<sys/time.h>
# include	<signal.h>
# include	<pthread.h>
# include	<stdbool.h>

# define EVEN 0
# define ODD 1

typedef struct s_param
{
	int	nb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	meals_per_philo;
	long	start_time;
}	t_param;

typedef enum e_state
{
	FORK		=	1,
	EAT			=	2,
	SLEEP		=	3,
	THINK		=	4,
	DIE			=	5,
}	t_state;

typedef struct s_ph
{
	t_param			*param;
	pthread_mutex_t *rfork;
	pthread_mutex_t *lfork;
	pthread_t		philosoph;
	long			last_meal;
	int				i;
	int				meal;
	bool			*alive;
}	t_ph;


void	*schedule(void *ph);

/*	UTILITIES.C */
long long	ft_atoi_ll(char *str);
void		free_data(t_ph *ph);

/*	TIMER.C */
long		get_time(void);
int	ft_sleep(long time, t_ph *ph);

/*	THREADS.C */
t_ph	*	create_philo(t_param *param);
int			join_philo(t_ph *ph, int philo);

/*	PRINTER.C */
size_t	ft_strlen(const char *s);
char	*ft_itoa(int n);
char	*ft_strjoin(char const *s1, char const *s2);
int		printer(long timer, int philo, int state);


int starving(t_ph *ph);

#endif
