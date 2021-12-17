/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:58:19 by ysonmez           #+#    #+#             */
/*   Updated: 2021/12/17 17:39:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_p_s.h"

/*
*/

static int	fill_philo(t_ph *ph, t_param *param)
{
	int	i;

	i = 0;
	while (i < param->nb_philo)
	{
		ph[i].i = i + 1;
		ph[i].last_meal = 0;
		ph[i].philo = fork();
		if (ph[i].philo == -1)
			exit(EXIT_FAILURE);
		if (ph[i].philo == 0)
		{
			schedule(&ph[i]);
			exit(EXIT_FAILURE);
		}
		i++;
		if (waitpid(-1, NULL, 0) != -1)
		{
			usleep(10000);
			if (param->nb_philo != 1)
				kill(0, SIGINT);
		}
	}
	return (0);
}

/*
*/

t_ph	*create_philo(t_param *param)
{
	t_ph	*ph;

	ph = (t_ph *)malloc(sizeof(t_ph) * (param->nb_philo));

	if (fill_philo(ph, param))
		return (NULL);
	return (ph);
}
