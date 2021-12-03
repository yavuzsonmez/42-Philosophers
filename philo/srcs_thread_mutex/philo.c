/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: home <home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 18:44:14 by ysonmez           #+#    #+#             */
/*   Updated: 2021/12/03 15:59:27 by home             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_t_m.h"

/*	Store and verify the parameters passed to the program */

size_t	parameters(char **argv, t_param *param)
{
	param->nb_philo = ft_atoi_ll(argv[1]);
	param->time_to_die = ft_atoi_ll(argv[2]);
	param->time_to_eat = ft_atoi_ll(argv[3]);
	param->time_to_sleep = ft_atoi_ll(argv[4]);
	if (argv[5] != NULL)
		param->meals_per_philo = ft_atoi_ll(argv[5]);
	if (param->nb_philo < 0 || param->nb_philo > 2147483647)
		return (1);
	else if (param->time_to_die < 0 || param->time_to_die > 2147483647)
		return (1);
	else if (param->time_to_eat < 0 || param->time_to_eat > 2147483647)
		return (1);
	else if (param->time_to_sleep < 0 || param->time_to_sleep > 2147483647)
		return (1);
	else if (param->meals_per_philo < 0 || param->meals_per_philo > 2147483647)
		return (1);
	return (0);
}

void	forks(t_ph *ph, long timer)
{
	while(1)
	{
		if (*(ph->rfork) == false)
		{
			printer(get_time() - timer, ph->i, FORK);
			pthread_mutex_lock(ph->rfork_mutex);
			*(ph->rfork) = true;
		}
		if (*(ph->lfork) == false)
		{
			printer(get_time() - timer, ph->i, FORK);
			pthread_mutex_lock(ph->lfork_mutex);
			*(ph->lfork) = true;
		}
		if (*(ph->rfork) == true && *(ph->lfork) == true)
			break ;
		ft_sleep(100);
	}
}


void	sleeping(t_ph *ph, long timer)
{
	printer(get_time() - timer, ph->i, SLEEP);
	ft_sleep(ph->param->time_to_sleep);
}

void	eating(t_ph *ph, long timer)
{
	if (*(ph->rfork) == true && *(ph->lfork) == true)
	{
		printer(get_time() - timer, ph->i, EAT);
		ph->last_meal = get_time() - timer;
		ft_sleep(ph->param->time_to_eat);
		*(ph->rfork) = false;
		*(ph->lfork) = false;
		pthread_mutex_unlock(ph->rfork_mutex);
		pthread_mutex_unlock(ph->lfork_mutex);
	}
}

void	thinking(t_ph *ph, long timer)
{
	printer(get_time() - timer, ph->i, THINK);
	ft_sleep(100);
}

void starving(t_ph *ph, long timer)
{
	timer = get_time() - timer;
	if (ph->param->time_to_die > timer - ph->last_meal)
	{
		printer(timer, ph->i, DIE);
		ph->alive = false;
	}
}

void init_dinner(t_ph *ph, long timer)
{
	if (ph->i % 2 == EVEN)
		eating(ph, timer);
	else
		thinking(ph, timer);
}

void	*schedule(void *ph)
{
	long start_time;

	start_time = get_time();
	init_dinner(ph, start_time);
	while (1)
	{
		forks(ph, start_time);
		eating(ph, start_time);
		sleeping(ph, start_time);
		thinking(ph, start_time);
		starving(ph, start_time);
		//if (fct check if someone died)
		//	return (NULL);
	}
	return (NULL);
}

/*	Philosophers with THREADS & MUTEX */

int main(int argc, char **argv)
{
	t_param		param;
	t_ph		*ph;

	if (argc < 5 || argc > 6)
		return (1);
	if (parameters(argv, &param))
		return (1);
	if (param.nb_philo == 0)
		return (0);
	else if (param.nb_philo == 1)
	{
		printer(0, 1, FORK);
		ft_sleep(param.time_to_die);
		printer(param.time_to_die, 1, DIE);
		return (0);
	}
	ph = create_philo(&param);
	if (ph == NULL)
		return (1);
	if (join_philo(ph, param.nb_philo))
		return (1);
	free_data(ph);
	return (0);
}