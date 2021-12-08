/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 16:47:32 by ysonmez           #+#    #+#             */
/*   Updated: 2021/12/08 13:14:11 by ysonmez          ###   ########.fr       */
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

/*	Long Long version of ft_atoi to handle bigger numbers */

long long	ft_atoi_ll(char *str)
{
	size_t			sign;
	size_t			i;
	long long		result;

	sign = 0;
	i = 0;
	result = 0;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			sign++;
		i++;
	}
	while (str[i] == 48)
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = result * 10 + ((str[i] - 48) % 10);
		i++;
	}
	if (sign % 2 == 1)
		return (result * (-1));
	return (result);
}

/*	Merge 2 strings into one */

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	s1len;
	size_t	s2len;
	char	*s;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	s = (char *)malloc(sizeof(char) * (s1len + s2len + 1));
	if (s == NULL)
		return (NULL);
	while (i < s1len)
	{
		s[i] = s1[i];
		i++;
	}
	while (j < s2len)
		s[i++] = s2[j++];
	s[i] = '\0';
	return (s);
}

void	free_data(t_ph *ph)
{
	int	i;
	int	philo;

	i = 0;
	philo = ph[0].param->nb_philo;
	while (i < philo)
	{
		free(ph[i].rfork);
		pthread_mutex_destroy(ph[i].rfork_mutex);
		free(ph[i].rfork_mutex);/*?*/
		i++;
	}
	free(ph);
}