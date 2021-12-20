/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diner.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 18:44:14 by ysonmez           #+#    #+#             */
/*   Updated: 2021/12/20 21:27:54 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_p_s.h"

/*	Sleeping function, after finishing the meal */

static int	sleeping(t_ph *ph)
{
	printer(ph, SLEEP);
	if (ft_sleep(ph->param->time_to_sleep, ph))
		return (1);
	return (0);
}

/*	Taking forks and eating, drop fork at the end */

static int	eating(t_ph *ph)
{
	sem_wait(ph->param->forks);
	printer(ph, FORK);
	sem_wait(ph->param->forks);
	printer(ph, FORK);
	ph->last_meal = get_time() - ph->param->start_time;
	printer(ph, EAT);
	if (ft_sleep(ph->param->time_to_eat, ph))
		return (1);
	sem_post(ph->param->forks);
	sem_post(ph->param->forks);
	ph->meal++;
	return (0);
}

/*	Thinking state, after eating and before getting a fork
*	Small sleep for the first thinkers of the diner for synchronisation
*/

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
	if (ph->param->nb_philo == 1)
	{
		printer(ph, FORK);
		ft_sleep(ph->param->time_to_die, ph);
		printer(ph, DIE);
		exit(EXIT_FAILURE);
	}
	if (ph->i % 2 == ODD)
		thinking(ph);
	while (1)
	{
		if (eating(ph))
			break ;
		if (ph->meal == ph->param->meals_per_philo)
			break ;
		if (sleeping(ph))
			break ;
		if (thinking(ph))
			break ;
	}
	if (ph->meal == ph->param->meals_per_philo)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
}
