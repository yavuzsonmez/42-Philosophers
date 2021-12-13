/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:58:19 by ysonmez           #+#    #+#             */
/*   Updated: 2021/12/13 12:29:03 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_t_m.h"

/*	Create the threadss and initialise their own data */

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
	while (i < param->nb_philo)
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
		if (pthread_create(&ph[i].philosoph, NULL, &schedule, (void *)&ph[i]))
			return (NULL);
		i++;
	}
	return (ph);
}

/*	Join threads at the end of the routine */

int	join_philo(t_ph *ph, int philo)
{
	int		i;

	i = 0;
	while (i < philo)
	{
		if (pthread_join(ph[i].philosoph, NULL))
			return (1);
		pthread_mutex_destroy(ph[i].rfork);
		i++;
	}
	return (0);
}
