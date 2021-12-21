/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 18:01:57 by ysonmez           #+#    #+#             */
/*   Updated: 2021/12/21 17:04:45 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_p_s.h"

/*	Returns the timestamp in milliseconds */

long	get_time(void)
{
	struct timeval	tp;
	long			milliseconds;

	gettimeofday(&tp, NULL);
	milliseconds = tp.tv_sec * 1000;
	milliseconds += tp.tv_usec / 1000;
	return (milliseconds);
}

void	ft_sleep(long s_time, t_ph *ph)
{
	long	sleep_start;
	long	current_time;

	sleep_start = get_time();
	current_time = sleep_start;
	while (sleep_start + s_time > current_time)
	{
		if (ph->param->time_to_die < (current_time - ph->param->start_time
				- ph->last_meal))
		{
			sem_wait(ph->param->end);
			printer(ph, DIE);
			sem_close(ph->param->print);
			sem_close(ph->param->forks);
			sem_close(ph->param->end);
			sem_unlink("/forks");
			sem_unlink("/print");
			sem_unlink("/end");
			exit(EXIT_FAILURE);
		}
		usleep(150);
		current_time = get_time();
	}
}
