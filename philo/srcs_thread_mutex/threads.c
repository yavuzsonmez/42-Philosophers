/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:58:19 by ysonmez           #+#    #+#             */
/*   Updated: 2021/12/02 19:05:04 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_t_m.h"

t_ph	*create_philo(t_param *param)
{
	t_ph	*ph;
	int		i;

	i = 0;
	ph = (t_ph *)malloc(sizeof(t_ph) * param->nb_philo);
	if (ph == NULL)
		return (NULL);
	while (i < param->nb_philo)
	{
		ph[i].i = i + 1;
		if (pthread_create(&ph[i].philosoph, NULL, &schedule, (void *)&ph[i]))
		{
			free(ph);
			return (NULL);
		}
		ph[i].fork = false;
		ph[i].alive = true;
		ph[i].state = NOT_INIT;
		ph[i].param = param;
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
			free(ph);
			return (1);
		}
		i++;
	}
	return (0);
}
