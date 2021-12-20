/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:58:19 by ysonmez           #+#    #+#             */
/*   Updated: 2021/12/20 16:56:28 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_p_s.h"

/*	Create each process (philosopher)
*	Fill data
*	Launch routine for each process (diner)
*	Wait for child process
*/

static int	fill_philo(t_param *param)
{
	t_ph	ph;
	int		i;
	int		status;
	pid_t	pid;

	i = 0;
	while (i < param->nb_philo)
	{
		ph.param = param;
		ph.meal = 0;
		ph.i = i + 1;
		ph.last_meal = 0;
		ph.philo = fork();
		if (ph.philo == -1)
			exit(EXIT_FAILURE);
		if (ph.philo == 0)
			schedule(&ph);
		i++;
	}
	waitpid(-1, &status, WEXITSTATUS(status));
	{
		if (status == 256)
			kill(0, SIGINT);
		while ((pid = wait(&status)) > 0);
		kill(0, SIGINT);
	}
	//if (status == 256)
	//	kill(0, SIGINT);
	//else if (status == 0)
	//{
	//	waitpid(-1, NULL, 0);
	//	kill(0, SIGINT);
	//}
	return (0);
}

/*	Create the data structure for philosophers,
*	and semaphores
*/

void	create_philo(t_param *param)
{
	sem_unlink("/forks");
	sem_unlink("/end");
	sem_unlink("/print");
	param->forks = sem_open("/forks", O_CREAT, 0660, param->nb_philo);
	if (param->forks == NULL)
		exit(EXIT_FAILURE);
	param->print = sem_open("/print", O_CREAT, 0660, 1);
	if (param->print == NULL)
		exit(EXIT_FAILURE);
	param->end = sem_open("/end", O_CREAT, 0660, 1);
	if (param->end == NULL)
		exit(EXIT_FAILURE);
	if (fill_philo(param))
		exit(EXIT_FAILURE);
	if (sem_unlink("/forks"))
		exit(EXIT_FAILURE);
	if (sem_unlink("/print"))
		exit(EXIT_FAILURE);
	if (sem_unlink("/end"))
		exit(EXIT_FAILURE);
}
