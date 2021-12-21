/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diner.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 18:44:14 by ysonmez           #+#    #+#             */
/*   Updated: 2021/12/21 18:50:35 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_p_s.h"

/*	Sleeping function, after finishing the meal */

static void	sleeping(t_ph *ph)
{
	printer(ph, SLEEP);
	ft_sleep(ph->param->time_to_sleep, ph);
}

/*	Taking forks and eating, drop fork at the end */

static void	eating(t_ph *ph)
{
	sem_wait(ph->param->forks);
	printer(ph, FORK);
	sem_wait(ph->param->forks);
	printer(ph, FORK);
	printer(ph, EAT);
	ft_sleep(ph->param->time_to_eat, ph);
	ph->last_meal = get_time() - ph->param->start_time;
	sem_post(ph->param->forks);
	sem_post(ph->param->forks);
	ph->meal++;
}

/*	Thinking state, after eating and before getting a fork
*	Small sleep for the first thinkers of the diner for synchronisation
*/

static void	thinking(t_ph *ph)
{
	printer(ph, THINK);
	if (ph->meal == 0)
		ft_sleep(100, ph);
}

/*	Routine for processes */

void	schedule(t_ph *ph)
{
	if (ph->param->nb_philo == 1)
	{
		printer(ph, FORK);
		ft_sleep(ph->param->time_to_die, ph);
		printer(ph, DIE);
		exit(EXIT_SUCCESS);
	}
	if (ph->i % 2 == EVEN)
		thinking(ph);
	while (1)
	{
		eating(ph);
		if (ph->meal == ph->param->meals_per_philo)
			break ;
		sleeping(ph);
		thinking(ph);
		usleep(100);
	}
	exit(EXIT_SUCCESS);
}
