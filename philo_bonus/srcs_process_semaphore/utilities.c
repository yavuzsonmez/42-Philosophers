/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 16:47:32 by ysonmez           #+#    #+#             */
/*   Updated: 2021/12/13 16:10:06 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_p_s.h"

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

/*	Free allocated memory */

int	free_data(t_ph *ph)
{
	int	i;
	int	philo;

	i = 0;
	philo = ph[0].param->nb_philo;
	while (i < philo)
	{
		if (ph[i].rfork != NULL)
			free(ph[i].rfork);
		i++;
	}
	if (ph->alive != NULL)
		free(ph->alive);
	if (ph != NULL)
		free(ph);
	return (0);
}
