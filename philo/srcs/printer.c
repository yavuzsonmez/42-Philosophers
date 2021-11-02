/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 19:15:12 by ysonmez           #+#    #+#             */
/*   Updated: 2021/11/02 10:13:05 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static char	*get_state(int state, const char *str)
{
	char	*buffer;

	if (state == FORK)
		buffer = ft_strjoin(str, "\thas taken a fork\n");
	else if (state == EAT)
		buffer = ft_strjoin(str, "\tis eating\n");
	else if (state == SLEEP)
		buffer = ft_strjoin(str, "\tis sleeping\n");
	else if (state == THINK)
		buffer = ft_strjoin(str, "\tis thinking\n");
	else if (state == DIE)
		buffer = ft_strjoin(str, "\tdied\n");
	else
		return (NULL);
	return (buffer);
}

void	printer(long timer, int philo, int state)
{
	char	*timestamp;
	char	*philo_number;
	char	*tmp;
	char	*tmp2;
	char	*buffer;

	timestamp = ft_itoa(timer);
	philo_number = ft_itoa(philo);
	tmp = ft_strjoin(timestamp, "\t");
	tmp2 = ft_strjoin(tmp, philo_number);
	buffer = get_state(state, tmp2);
	write(1, buffer, ft_strlen(buffer));
	free(philo_number);
	free(timestamp);
	free(tmp);
	free(tmp2);
	free(buffer);
}
