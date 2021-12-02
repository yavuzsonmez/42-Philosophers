/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 18:44:14 by ysonmez           #+#    #+#             */
/*   Updated: 2021/12/02 19:16:49 by ysonmez          ###   ########.fr       */
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

/*
void	take_rfork(t_data *data, long timer, int i)
{
	pthread_mutex_t	mutex;
	if (pthread_mutex_init(&mutex, NULL))
		return ;
	pthread_mutex_lock(&mutex);
	data->philo[(i + 1) % data->param.nb_philo].fork = true;
	printer(timer, data->philo[i].i, FORK);
	pthread_mutex_unlock(&mutex);
	pthread_mutex_destroy(&mutex);
}

void	take_lfork(t_data *data, long timer, int i)
{
	pthread_mutex_t	mutex;
	if (pthread_mutex_init(&mutex, NULL))
		return ;
	pthread_mutex_lock(&mutex);
	data->philo[i].fork = true;
	printer(timer, data->philo[i].i, FORK);
	pthread_mutex_unlock(&mutex);
	pthread_mutex_destroy(&mutex);
}


void	sleeping(t_data *data, long start_time, int i)
{
	data->philo[0].state = SLEEP;
	printer(start_time, data->philo[0].i, SLEEP);
	ft_sleep(data->param.time_to_sleep);
}
*/
void	eating(t_ph *ph, long timer)
{
	//take_rfork(data, timer, i);
	//take_lfork(data, timer, i);
	//if (data->philo[i].fork == true && data->philo[(i + 1) % data->param.nb_philo].fork == true)
	//{
	//	printer(timer, data->philo[i].i, EAT);
	//	ft_sleep(data->param.time_to_eat);
	//}
	//data->philo[i].fork = false;
	//data->philo[(i + 1) % data->param.nb_philo].fork = false;
	printer(get_time() - timer, ph->i, EAT);
	ft_sleep(ph->param->time_to_eat);

}

void	thinking(t_ph *ph, long timer)
{
	printer(get_time() - timer, ph->i, THINK);
	ft_sleep(100);
}

void init_dinner(t_ph *ph, long timer)
{
	if (ph->i % 2 == ODD)
	{
		eating(ph, timer);
	}
	else
	{
		thinking(ph, timer);
	}
}

void	*schedule(void *ph)
{
	long start_time;

	start_time = get_time();
	init_dinner(ph, start_time);
	//eating(data, get_time() - start_time);
	//while (1)
	//{
	//	eating(data, get_time() - start_time);
	//	sleeping(data, get_time() - start_time);
	//	thinking(data, get_time() - start_time);
	//}
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
	//free();
	return (0);
}