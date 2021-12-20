/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 11:53:57 by ysonmez           #+#    #+#             */
/*   Updated: 2021/12/20 15:16:01 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_p_s.h"

/*	Check if the character is a digit or not */

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (0);
	else
		return (1);
}

/*	Check if the philo parameters are  */

static size_t	only_digit(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i] != NULL)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (ft_isdigit(argv[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

/*	Store and verify the parameters passed to the program */

static size_t	parameters(char **argv, t_param *param)
{
	param->nb_philo = ft_atoi_ll(argv[1]);
	param->time_to_die = ft_atoi_ll(argv[2]);
	param->time_to_eat = ft_atoi_ll(argv[3]);
	param->time_to_sleep = ft_atoi_ll(argv[4]);
	param->start_time = get_time();
	if (argv[5] != NULL)
	{
		param->meals_per_philo = ft_atoi_ll(argv[5]);
		if (param->meals_per_philo < 0 || param->meals_per_philo > 2147483647)
			return (1);
	}
	else
		param->meals_per_philo = -1;
	if (param->nb_philo < 0 || param->nb_philo > 2147483647)
		return (1);
	else if (param->time_to_die < 0 || param->time_to_die > 2147483647)
		return (1);
	else if (param->time_to_eat < 0 || param->time_to_eat > 2147483647)
		return (1);
	else if (param->time_to_sleep < 0 || param->time_to_sleep > 2147483647)
		return (1);
	return (0);
}

/*	Philosophers with PROCESSES & SEMAPHORES */

int	main(int argc, char **argv)
{
	t_param		param;

	if (argc < 5 || argc > 6)
		return (1);
	if (only_digit(argv))
		return (1);
	if (parameters(argv, &param))
		return (1);
	if (param.nb_philo == 0)
		return (0);
	create_philo(&param);
	return (0);
}
