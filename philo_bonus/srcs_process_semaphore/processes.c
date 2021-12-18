/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: node <node@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:58:19 by ysonmez           #+#    #+#             */
/*   Updated: 2021/12/18 14:04:17 by node             ###   ########.fr       */
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
		ph[i].param = param;
		ph[i].i = i + 1;
		ph[i].last_meal = 0;
		ph[i].print = ph[0].print;
		ph[i].forks = ph[0].forks;
		ph[i].end = ph[0].end;
		ph[i].philo = fork();
		if (ph[i].philo == -1)
			exit(EXIT_FAILURE);
		if (ph[i].philo == 0)
		{
			schedule(&ph[i]);
			return (0);
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
	//ph->print = (sem_t *)malloc(sizeof(sem_t));
	//ph->forks = (sem_t *)malloc(sizeof(sem_t));
	//ph->end = (sem_t *)malloc(sizeof(sem_t));
	ph->print = sem_open("/print", O_CREAT, 0660, 1);
	ph->forks = sem_open("/forks", O_CREAT, 0660, param->nb_philo);
	ph->end = sem_open("/end", O_CREAT, 0660, 1);
	if (fill_philo(ph, param))
		return (NULL);
	return (ph);
}
