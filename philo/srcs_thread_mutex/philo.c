/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: home <home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 18:44:14 by ysonmez           #+#    #+#             */
/*   Updated: 2021/12/04 17:22:52 by home             ###   ########.fr       */
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

int control(t_ph *ph)
{
	int	i;

	i = 0;
	while (i < ph[0].param->nb_philo)
	{
		if (ph->data[i].alive == false)
			return (1);
		i++;
	}
	return (0);
}

int starving(t_ph *ph, long timer)
{
	if (ph->param->time_to_die < timer - ph->last_meal)
	{
		//printf("time to die%d, timer %ld, last meal %ld, calcul %ld\n", ph->param->time_to_die, timer, ph->last_meal, timer - ph->last_meal);
		printer(timer, ph->i, DIE);
		ph->alive = false;
	}
	if (control(ph))
		return (1);
	return (0);
}

int	forks(t_ph *ph, long timer)
{
	while(1)
	{
		if (*(ph->rfork) == false && *(ph->lfork) == false)
		{
			timer = get_time() - timer;
			pthread_mutex_lock(ph->rfork_mutex);
			*(ph->rfork) = true;
			pthread_mutex_unlock(ph->rfork_mutex);
			printer(timer, ph->i, FORK);
			pthread_mutex_lock(ph->lfork_mutex);
			*(ph->lfork) = true;
			pthread_mutex_unlock(ph->lfork_mutex);
			printer(timer, ph->i, FORK);
			return (0);
		}
		if (starving(ph, get_time() - timer))
			return (1);
	}
}

int	sleeping(t_ph *ph, long timer)
{
	if(starving(ph, get_time() - timer))
		return (1);
	printer(get_time() - timer, ph->i, SLEEP);
	ft_sleep(ph->param->time_to_sleep);
	if(starving(ph, get_time() - timer))
		return (1);
	return (0);
}

void	eating(t_ph *ph, long timer)
{
	if (*(ph->rfork) == true && *(ph->lfork) == true)
	{
		timer = get_time() - timer;
		printer(timer, ph->i, EAT);
		ph->last_meal = timer;
		ft_sleep(ph->param->time_to_eat);
		pthread_mutex_lock(ph->rfork_mutex);
		*(ph->rfork) = false;
		pthread_mutex_unlock(ph->rfork_mutex);
		pthread_mutex_lock(ph->lfork_mutex);
		*(ph->lfork) = false;
		pthread_mutex_unlock(ph->lfork_mutex);
		ph->meal++;
	}
}

int	thinking(t_ph *ph, long timer)
{
	int	i;

	i = 0;
	if (ph->param->time_to_die < (get_time() - timer - ph->last_meal))
		return (0);
	printer(get_time() - timer, ph->i, THINK);
	while(i < 20)
	{
		ft_sleep(5);
		i++;
		if(starving(ph, get_time() - timer))
			return (1);
	}
	if(starving(ph, get_time() - timer))
		return (1);
	return (0);
}

void	*schedule(void *ph)
{
	long start_time;

	start_time = get_time();
	if (((t_ph *)ph)->i % 2 == ODD)
		thinking(ph, start_time);
	while (1)
	{
		if (((t_ph *)ph)->meal == ((t_ph *)ph)->param->meals_per_philo)
			break ;
		if(forks(ph, start_time))
			break ;
		eating(ph, start_time);
		if(sleeping(ph, start_time))
			break ;
		if(thinking(ph, start_time))
			break ;
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