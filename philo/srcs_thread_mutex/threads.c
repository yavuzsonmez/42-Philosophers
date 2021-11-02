/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:58:19 by ysonmez           #+#    #+#             */
/*   Updated: 2021/11/02 12:59:01 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_t_m.h"

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
		data->state = NOT_INIT;
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
