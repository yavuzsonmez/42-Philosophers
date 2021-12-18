/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: node <node@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 18:44:14 by ysonmez           #+#    #+#             */
/*   Updated: 2021/12/18 14:01:44 by node             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_p_s.h"

static int	sleeping(t_ph *ph)
{
	printer(ph, SLEEP);
	if (ft_sleep(ph->param->time_to_sleep, ph))
		return (1);
	return (0);
}


static int	eating(t_ph *ph)
{
	sem_wait(ph->forks);
	printer(ph, FORK);
	sem_wait(ph->forks);
	printer(ph, FORK);
	ph->last_meal = get_time() - ph->param->start_time;
	printer(ph, EAT);
	if (ft_sleep(ph->param->time_to_eat, ph))
	{
		//sem_post(ph->forks);
		//sem_post(ph->forks);
		return (1);
	}
	ph->meal++;
	sem_post(ph->forks);
	sem_post(ph->forks);
	return (0);
}


static int	thinking(t_ph *ph)
{
	printer(ph, THINK);
	if (ph->meal == 0)
	{
		if (ft_sleep(100, ph))
			return (1);
	}
	return (0);
}


/*	Routine for processes */

void	schedule(t_ph *ph)
{
	if (ph->i % 2 == ODD)
		thinking(ph);
	while (1)
	{
		if (ph->meal == ph->param->meals_per_philo)
			break ;
		if (eating(ph))
			break ;
		if (sleeping(ph))
			break ;
		if (thinking(ph))
			break ;
	}
	sem_close(ph->print);
	sem_close(ph->forks);
	sem_close(ph->end);
	return ;
}
