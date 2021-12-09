/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: home <home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:58:19 by ysonmez           #+#    #+#             */
/*   Updated: 2021/12/09 18:44:35 by home             ###   ########.fr       */
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
	if (ph == NULL || alive == NULL)
		return (NULL);
	*alive = true;
	ph[0].die = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(ph[0].die, NULL);
	while(i < param->nb_philo)
	{
		ph[i].rfork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(ph[i].rfork, NULL);
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
		ph[i].die = ph[0].die;
		ph[i].arr = &ph[0];
		if (pthread_create(&ph[i].philosoph, NULL, &schedule, (void *)&ph[i]))
		{
			//free(ph);
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
			//free_data(ph);
			return (1);
		}
		if (i == 0)
			pthread_mutex_destroy(ph[i].die);
		pthread_mutex_destroy(ph[i].rfork);
		i++;
	}
	return (0);
}
