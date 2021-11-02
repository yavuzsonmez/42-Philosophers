/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 18:44:14 by ysonmez           #+#    #+#             */
/*   Updated: 2021/11/02 10:15:39 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

void	eat(t_data *data, long start_time)
{
	if (data->philo[0].fork_in_use == false)
	{
		printer(get_time() - start_time, data->philo[0].i, FORK);
		ft_sleep(100);
	}
}

void	*schedule(void *data)
{
	long start_time;

	start_time = get_time();
	while (1)
	{
		eat(data, start_time);
	}
	return (NULL);
}

int	create_philo(t_data *data)
{
	int		i;

	i = 0;
	data->philo = (t_ph *)malloc(sizeof(t_ph) * data->param.nb_philo);
	if (data->philo == NULL)
		return (1);
	while (i < data->param.nb_philo)
	{
		data->philo[i].i = i + 1;
		if (pthread_create(&data->philo[i].philosoph, NULL, &schedule, (void *)data))
		{
			free(data->philo);
			return (1);
		}
		data->philo[i].fork_in_use = false;
		data->philo[i].alive = true;
		i++;
	}
	return (0);
}

int	join_philo(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->param.nb_philo)
	{
		if (pthread_join(data->philo[i].philosoph, NULL))
		{
			free(data->philo);
			return (1);
		}
		i++;
	}
	return (0);
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