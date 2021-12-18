/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: node <node@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:58:19 by ysonmez           #+#    #+#             */
/*   Updated: 2021/12/18 17:09:20 by node             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_p_s.h"

/*	Create each process (philosopher)
*	Fill data
*	Launch routine for each process (diner)
*	Wait for child process
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
		ph[i].philo = fork();
		if (ph[i].philo == -1)
			exit(EXIT_FAILURE);
		if (ph[i].philo == 0)
		{
			schedule(&ph[i]);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
	waitpid(-1, NULL, 0);
	kill(0, SIGINT);
	return (0);
}

/*	Create the data structure for philosophers,
*	and semaphores
*/

t_ph	*create_philo(t_param *param)
{
	t_ph	*ph;

	ph = (t_ph *)malloc(sizeof(t_ph) * (param->nb_philo));
	if (ph == NULL)
		return (NULL);
	if (sem_unlink("/forks"))
		return (NULL);
	if (sem_unlink("/print"))
		return (NULL);
	if (sem_unlink("/end"))
		return (NULL);
	param->forks = sem_open("/forks", O_CREAT, 0660, param->nb_philo);
	if (param->forks == NULL)
		return (NULL);
	param->print = sem_open("/print", O_CREAT, 0660, 1);
	if (param->print == NULL)
		return (NULL);
	param->end = sem_open("/end", O_CREAT, 0660, 1);
	if (param->end == NULL)
		return (NULL);
	param->alive = true;
	if (fill_philo(ph, param))
		return (NULL);
	return (ph);
}
