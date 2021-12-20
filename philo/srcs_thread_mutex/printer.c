/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 19:15:12 by ysonmez           #+#    #+#             */
/*   Updated: 2021/12/20 20:52:09 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_t_m.h"

/*	Return string length */

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

/*	Buffer version of putnbr */

static void	putnbr_buff(int n, char **buff)
{
	unsigned int	number;

	if (n < 0)
	{
		number = n * (-1);
		*(*buff)++ = '-';
	}
	else
		number = n;
	if (number >= 10)
		putnbr_buff(number / 10, buff);
	*(*buff)++ = (number % 10) + 48;
}

/*	Buffer version of putstr */

static void	putstr_buff(char *s, char **buff)
{
	int	i;

	i = 0;
	if (s != NULL)
	{
		while (s[i] != '\0')
		{
			*(*buff)++ = s[i];
			i++;
		}
		*(*buff) = '\0';
	}
}

/*	Fct which print each state of the philosophers
*		2 steps :
*					- Creation de buffer with the string we want to print
*					- Printing with one write only to save syscall and performance
*/

int	printer(t_ph *ph, int state)
{
	char	*ptr;
	char	buff[128];
	int		len;

	ptr = buff;
	putnbr_buff(get_time() - ph->param->start_time, &ptr);
	putstr_buff("\t", &ptr);
	putnbr_buff(ph->i, &ptr);
	if (state == FORK)
		putstr_buff("\thas taken a fork\n", &ptr);
	else if (state == EAT)
		putstr_buff("\tis eating\n", &ptr);
	else if (state == SLEEP)
		putstr_buff("\tis sleeping\n", &ptr);
	else if (state == THINK)
		putstr_buff("\tis thinking\n", &ptr);
	else if (state == DIE)
		putstr_buff("\tdied\n", &ptr);
	len = ft_strlen(buff);
	pthread_mutex_lock(ph->print);
	write(1, buff, len);
	pthread_mutex_unlock(ph->print);
	return (0);
}
