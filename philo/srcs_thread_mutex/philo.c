/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 18:44:14 by ysonmez           #+#    #+#             */
/*   Updated: 2021/12/08 21:09:40 by ysonmez          ###   ########.fr       */
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
	param->start_time = get_time();
	if (argv[5] != NULL)
	{
		param->meals_per_philo = ft_atoi_ll(argv[5]);
		if (param->meals_per_philo < 0 || param->meals_per_philo > 2147483647)
			return (1);
	}
	else
		param->meals_per_philo = -1;
	if (param->nb_philo < 0 || param->nb_philo > 2147483647)
		return (1);
	else if (param->time_to_die < 0 || param->time_to_die > 2147483647)
		return (1);
	else if (param->time_to_eat < 0 || param->time_to_eat > 2147483647)
		return (1);
	else if (param->time_to_sleep < 0 || param->time_to_sleep > 2147483647)
		return (1);
	return (0);
}

int starving(t_ph *ph)
{
	long	timer;

	if (*(ph->alive) == false)
		return (1);
	timer = get_time() - ph->param->start_time;
	if (ph->param->time_to_die < timer - ph->last_meal)
	{
		printer(timer, ph->i, DIE);
		*(ph->alive) = false;
		return (1);
	}
	return (0);
}

int	sleeping(t_ph *ph)
{
	if (*(ph->alive) == false)
		return (1);
	printer(get_time() - ph->param->start_time, ph->i, SLEEP);
	if (ft_sleep(ph->param->time_to_sleep, ph))
		return (1);
	return (0);
}

int	eating(t_ph *ph)
{
	long	timer;

	if (*(ph->alive) == false)
		return (1);

	pthread_mutex_lock(ph->rfork);
	pthread_mutex_lock(ph->lfork);
	timer = get_time() - ph->param->start_time;
	printer(timer, ph->i, FORK);
	printer(timer, ph->i, FORK);
	ph->last_meal = timer;
	printer(timer, ph->i, EAT);
	if (ft_sleep(ph->param->time_to_eat, ph))
		return (1);
	pthread_mutex_unlock(ph->rfork);
	pthread_mutex_unlock(ph->lfork);
	ph->meal++;
	return (0);
}

int	thinking(t_ph *ph, int i)
{
	if (*(ph->alive) == false)
		return (1);
	printer(get_time() - ph->param->start_time, ph->i, THINK);
	if (i == 1)
		ft_sleep(ph->param->time_to_eat, ph);
	return (0);
}

void	*schedule(void *ph)
{
	long start_time;

	start_time = get_time();
	if (((t_ph *)ph)->i % 2 == ODD)
		thinking(ph, 1);
	while (1)
	{
		if (((t_ph *)ph)->meal == ((t_ph *)ph)->param->meals_per_philo)
			break ;
		if(eating(ph))
			break ;
		if (sleeping(ph))
			break ;
		thinking(ph, 0);
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
		ft_sleep(param.time_to_die, NULL);
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