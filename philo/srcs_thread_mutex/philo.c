/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 18:44:14 by ysonmez           #+#    #+#             */
/*   Updated: 2021/11/02 13:25:15 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_t_m.h"

/*	Getting the parameters passed to the program */

size_t	parameters(char **argv, t_data *data)
{
	data->param.nb_philo = ft_atoi_ll(argv[1]);
	data->param.time_to_die = ft_atoi_ll(argv[2]);
	data->param.time_to_eat = ft_atoi_ll(argv[3]);
	data->param.time_to_sleep = ft_atoi_ll(argv[4]);
	if (argv[5] != NULL)
		data->param.meals_per_philo = ft_atoi_ll(argv[5]);
	if (data->param.nb_philo < 0 || data->param.nb_philo > 2147483647)
		return (1);
	else if (data->param.time_to_die < 0 || data->param.time_to_die > 2147483647)
		return (1);
	else if (data->param.time_to_eat < 0 || data->param.time_to_eat > 2147483647)
		return (1);
	else if (data->param.time_to_sleep < 0 || data->param.time_to_sleep > 2147483647)
		return (1);
	else if (argv[5] != NULL && (data->param.time_to_sleep < 0
		|| data->param.time_to_sleep > 2147483647))
		return (1);
	return (0);

}

void	eating(t_data *data, long start_time)
{
	pthread_mutex_t	mutex;

	pthread_mutex_init(&mutex, NULL);
	if (data->philo[0].fork_in_use == false && data->philo[0 + 1].fork_in_use == false)
	{
		pthread_mutex_lock(&mutex);
		data->philo[0].fork_in_use = true;
		data->philo[0 + 1].fork_in_use = true;
		printer(start_time, data->philo[0].i, FORK);
		printer(start_time, data->philo[0].i, FORK);
		data->philo[0].state = EAT;
		printer(start_time, data->philo[0].i, EAT);
		ft_sleep(data->param.time_to_eat);
		data->philo[0].fork_in_use = false;
		data->philo[0 + 1].fork_in_use = false;
		pthread_mutex_unlock(&mutex);
	}
	pthread_mutex_destroy(&mutex);
}

void	sleeping(t_data *data, long start_time)
{
	data->philo[0].state = SLEEP;
	printer(start_time, data->philo[0].i, SLEEP);
	ft_sleep(data->param.time_to_sleep);
}

void	thinking(t_data *data, long start_time)
{
	data->philo[0].state = THINK;
	printer(start_time, data->philo[0].i, THINK);
	ft_sleep(100);
}

void	*schedule(void *data)
{
	long start_time;

	start_time = get_time();
	while (1)
	{
		eating(data, get_time() - start_time);
		sleeping(data, get_time() - start_time);
		thinking(data, get_time() - start_time);
	}
	return (NULL);
}


/*	Philosophers with THREADS & MUTEX */

int main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (1);
	if (parameters(argv, &data))
		return (1);
	if(create_philo(&data))
		return (1);
	if (join_philo(&data))
		return (1);
	free(data.philo);
	return (0);
}