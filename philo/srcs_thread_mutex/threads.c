/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:58:19 by ysonmez           #+#    #+#             */
/*   Updated: 2021/12/08 21:06:49 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_t_m.h"

t_ph	*create_philo(t_param *param)
{
	t_ph	*ph;
	int		i;
	bool	*alive;

	i = 0;
	ph = (t_ph *)malloc(sizeof(t_ph) * (param->nb_philo));
	alive = (bool *)malloc(sizeof(bool));
	*alive = true;
	if (ph == NULL)
		return (NULL);
	while(i < param->nb_philo)
	{
		ph[i].rfork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (pthread_mutex_init(ph[i].rfork, NULL) != 0)
		{
			free(ph);
			return (NULL);
		}
		i++;
	}
	i = 0;
	while (i < param->nb_philo)
	{
		ph[i].i = i + 1;
		ph[i].lfork = ph[(i + 1) % param->nb_philo].rfork;
		ph[i].alive = alive;
		ph[i].param = param;
		ph[i].last_meal = 0;
		ph[i].meal = 0;
		if (pthread_create(&ph[i].philosoph, NULL, &schedule, (void *)&ph[i]))
		{
			free(ph);
			return (NULL);
		}
		i++;
	}
	return (ph);
}

int	join_philo(t_ph *ph, int philo)
{
	int		i;

	i = 0;
	while (i < philo)
	{
		if (pthread_join(ph[i].philosoph, NULL))
		{
			free_data(ph);
			return (1);
		}
		i++;
	}
	return (0);
}
