/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 19:15:12 by ysonmez           #+#    #+#             */
/*   Updated: 2021/12/08 20:35:36 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_t_m.h"

static void	putnbr_buff(int n, char **buff)
{
	unsigned int	number;
	char			c;

	c = 0;
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

int	printer(long timer, int philo, int state)
{
	char	*ptr;
	char	buff[128];
	int		len;

	ptr = buff;
	putnbr_buff(timer, &ptr);
	putstr_buff("\t", &ptr);
	putnbr_buff(philo, &ptr);
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
	write(1, buff, len);
	return (0);
}
