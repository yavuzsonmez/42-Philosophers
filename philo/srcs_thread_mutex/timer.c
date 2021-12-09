/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: home <home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 18:01:57 by ysonmez           #+#    #+#             */
/*   Updated: 2021/12/09 19:32:42 by home             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_t_m.h"

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

/*	Using usleep directly can introduce significant delays because
*	`man usleep` says that `usleep` will sleep at least n milliseconds
*		Why ?
*				"The sleep may be lengthened slightly by any system activity
*				or by the time spent processing the call or by the
*				granularity of system timers"
*
*	This function fix that and introduce not more than
*	1-2 milliseconds each loop in our case
*/

int	ft_sleep(long s_time, t_ph *ph)
{
	long	sleep_start;
	long	current_time;

	sleep_start = get_time();
	current_time = sleep_start;
	while (sleep_start + s_time > current_time)
	{
		if(*(ph->alive) == false)
		{
			return (1);
		}
		if (ph->param->time_to_die < (current_time - ph->param->start_time - ph->last_meal))
		{
			printer(ph, DIE);
			*(ph->alive) = false;
			return (1);
		}
		usleep(100);
		current_time = get_time();
	}
	return (0);
}

