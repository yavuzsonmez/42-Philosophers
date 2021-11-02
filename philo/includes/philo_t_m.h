/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_t_m.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 18:44:16 by ysonmez           #+#    #+#             */
/*   Updated: 2021/11/02 15:31:14 by ysonmez          ###   ########.fr       */
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
}	t_param;

typedef enum e_state
{
	NOT_INIT	=	0,
	FORK		=	1,
	EAT			=	2,
	SLEEP		=	3,
	THINK		=	4,
	DIE			=	5,
}	t_state;

typedef struct s_ph
{
	int			i;
	pthread_t	philosoph;
	bool		fork_in_use;
	bool		alive;
	int			state;
}	t_ph;

typedef struct s_data
{
	t_param				param;
	t_ph				*philo;
	t_state				state;
}	t_data;

void	*schedule(void *data);

/*	UTILITIES.C */
long long	ft_atoi_ll(char *str);

/*	TIMER.C */
long		get_time(void);
void		ft_sleep(long time);

/*	THREADS.C */
int			create_philo(t_data *data);
int			join_philo(t_data *data);

/*	PRINTER.C */
size_t	ft_strlen(const char *s);
char	*ft_itoa(int n);
char	*ft_strjoin(char const *s1, char const *s2);
int		printer(long timer, int philo, int state);

#endif
