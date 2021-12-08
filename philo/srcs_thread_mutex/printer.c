/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 19:15:12 by ysonmez           #+#    #+#             */
/*   Updated: 2021/12/08 17:53:59 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_t_m.h"

/*
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

int	printer(long timer, int philo, int state)
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
	if (buffer == NULL)
		return (1);
	write(1, buffer, ft_strlen(buffer));
	free(philo_number);
	free(timestamp);
	free(tmp);
	free(tmp2);
	free(buffer);
	return (0);
}
*/

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

/*

static void        putnbr_buff(size_t nbr, char **buff)
{
    if (nbr / 10)
        putnbr_buff(nbr / 10, buff);
    *(*buff)++ = (char)(nbr % 10 + '0');
}

static void        putstr_buff(char *str, char **buff)
{
    while (*str)
        *(*buff)++ = *str++;
}
*/