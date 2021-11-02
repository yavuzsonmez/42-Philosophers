/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 18:01:57 by ysonmez           #+#    #+#             */
/*   Updated: 2021/11/02 11:05:55 by ysonmez          ###   ########.fr       */
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

void	ft_sleep(long time)
{
	long	start_time;
	start_time = get_time();

	while (start_time + time > get_time())
	{
			usleep(100);
	}
	return ;
}
