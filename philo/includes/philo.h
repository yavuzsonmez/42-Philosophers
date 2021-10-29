/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 18:44:16 by ysonmez           #+#    #+#             */
/*   Updated: 2021/10/29 20:53:33 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

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
#include	<sys/time.h>
# include	<signal.h>
#include	<pthread.h>
#include	<stdbool.h>



typedef struct s_param
{
	int	nb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	meals_per_philo;
}	t_param;

//typedef enum s_state
//{
//
//}	t_state;

typedef struct s_ph
{
	int			i;
	pthread_t	philosoph;
	bool		fork_in_use;
	bool		alive;
}	t_ph;

/*	UTILITIES.C */
long long	ft_atoi_ll(char *str);

/*	TIMER.C */
long		get_time(void);
void		ft_sleep(long time);

/*	PRINTER.C */

#endif
