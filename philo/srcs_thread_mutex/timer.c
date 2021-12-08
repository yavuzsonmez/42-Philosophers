/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 18:01:57 by ysonmez           #+#    #+#             */
/*   Updated: 2021/12/08 20:10:30 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_t_m.h"

/*	Returns the timestamp in milliseconds */

long    get_time(void)
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

int	ft_sleep(long time, t_ph *ph)
{
	long	sleep_start;

	sleep_start = get_time();
	while (sleep_start + time > get_time())
	{
		if (ph != NULL)
		{
			if (*(ph->alive) == false)
				return (1);
			if (starving(ph))
				return (1) ;
		}
		usleep(10);
	}
	return (0);
}
