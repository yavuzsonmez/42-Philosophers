/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:58:19 by ysonmez           #+#    #+#             */
/*   Updated: 2021/12/13 16:10:02 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_p_s.h"

/*	Create each thread (philosopher)
*	First create one fork for each philo (Right hand fork)
*	Left hand fork is the Right hand fork of the next philo
*	Fill data
*/

static int	fill_philo(t_ph *ph, t_param *param)
{
	int	i;

	i = 0;
	while (i < param->nb_philo)
	{
		ph[i].rfork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (pthread_mutex_init(ph[i].rfork, NULL))
			return (1);
		i++;
	}
	i = 0;
	while (i < param->nb_philo)
	{
		ph[i].i = i + 1;
		ph[i].lfork = ph[(i + 1) % param->nb_philo].rfork;
		ph[i].alive = ph[0].alive;
		ph[i].param = param;
		ph[i].last_meal = 0;
		ph[i].meal = 0;
		ph[i].print = ph[0].print;
		if (pthread_create(&ph[i].philosoph, NULL, &schedule, (void *)&ph[i]))
			return (1);
		i++;
	}
	return (0);
}

/*	Create the initial data struct
*	Each struct in the array contain the philo (thread) and his own data
*	Init shared var :	Printing mutex and
*						Alive var(to stop the simulation if a philo die)
*/

t_ph	*create_philo(t_param *param)
{
	t_ph	*ph;

	ph = (t_ph *)malloc(sizeof(t_ph) * (param->nb_philo));
	ph->alive = (bool *)malloc(sizeof(bool));
	ph->print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (ph == NULL || ph->alive == NULL || ph->print == NULL)
		return (NULL);
	*(ph->alive) = true;
	if (pthread_mutex_init(ph->print, NULL))
		return (NULL);
	if (fill_philo(ph, param))
		return (NULL);
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
