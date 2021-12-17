/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 18:44:14 by ysonmez           #+#    #+#             */
/*   Updated: 2021/12/17 17:42:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_p_s.h"


/*
static int	sleeping(t_ph *ph)
{
	if (*(ph->alive) == true)
		printer(ph, SLEEP);
	if (ft_sleep(ph->param->time_to_sleep, ph))
		return (1);
	return (0);
}


static int	eating(t_ph *ph)
{
	long	timer;

	pthread_mutex_lock(ph->lfork);
	if (*(ph->alive) == true)
		printer(ph, FORK);
	pthread_mutex_lock(ph->rfork);
	timer = get_time() - ph->param->start_time;
	if (*(ph->alive) == true)
		printer(ph, FORK);
	ph->last_meal = timer;
	if (*(ph->alive) == true)
		printer(ph, EAT);
	if (ft_sleep(ph->param->time_to_eat, ph))
	{
		pthread_mutex_unlock(ph->rfork);
		pthread_mutex_unlock(ph->lfork);
		return (1);
	}
	pthread_mutex_unlock(ph->rfork);
	pthread_mutex_unlock(ph->lfork);
	ph->meal++;
	return (0);
}
*/

static void	thinking(t_ph *ph)
{
	(void)ph;
	printf("im sleeping\n");
	usleep(100000);
}


/*	Routine for processes */

void	schedule(t_ph *ph)
{
	int i;
	//sem_t *sem;

	if (ph->i % 2 == ODD)
		thinking(ph);
	//sem = sem_open("/print", O_CREAT);
	i = 0;
	while (1)
	{
		//sem_wait(sem);
		//printer(ph, EAT);
		printf("Hello I am philo %d and my pid is %d\n", ph->i, ph->philo);
		//sem_post(sem);
		if (i == 10)
			break ;
		i++;
	}
	//sem_close(sem);
	return ;
}
