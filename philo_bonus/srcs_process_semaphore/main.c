/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 11:53:57 by ysonmez           #+#    #+#             */
/*   Updated: 2021/12/17 15:05:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_p_s.h"

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
	t_ph		*ph;

	if (argc < 5 || argc > 6)
		return (1);
	if (parameters(argv, &param))
		return (1);
	if (param.nb_philo == 0)
		return (0);
	ph = create_philo(&param);
	if (ph == NULL && free_data(ph) == 0)
		return (1);
	// if (param.nb_philo == 1)
	// {
	// 	printer(ph, FORK);
	// 	ft_sleep(param.time_to_die, ph);
	// 	printer(ph, DIE);
	// }
	free_data(ph);
	return (0);
}
