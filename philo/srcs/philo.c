/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 18:44:14 by ysonmez           #+#    #+#             */
/*   Updated: 2021/10/28 17:40:24 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*	Getting the parameters passed to the program */

size_t	parameters(char **argv, t_ph *ph)
{
	printf("HELLO\n");
	ph->param.nb_philo = ft_atoi_ll(argv[1]);
	ph->param.time_to_die = ft_atoi_ll(argv[2]);
	ph->param.time_to_eat = ft_atoi_ll(argv[3]);
	ph->param.time_to_sleep = ft_atoi_ll(argv[4]);
	if (argv[5] != NULL)
		ph->param.meals_per_philo = ft_atoi_ll(argv[5]);
	printf("Nb of philo %d\n", ph->param.nb_philo);
	//if (ph->param.nb_philo < 0 || ph->param.nb_philo > 2147483647)
	//	return (1);
	//else if (ph->param.time_to_die < 0 || ph->param.time_to_die > 2147483647)
	//	return (1);
	//else if (ph->param.time_to_eat < 0 || ph->param.time_to_eat > 2147483647)
	//	return (1);
	//else if (ph->param.time_to_sleep < 0 || ph->param.time_to_sleep > 2147483647)
	//	return (1);
	//else if (argv[5] != NULL && (ph->param.time_to_sleep < 0 || ph->param.time_to_sleep > 2147483647))
	//	return (1);
	return (0);

}

/*	Philosophers with THREADS & MUTEX */

int main(int argc, char **argv)
{
	t_ph	ph;
	if (argc < 5 || argc > 6)
		return (1);
	if (parameters(argv, &ph))
		return (1);
	printf("TEST!!\nNumber of philo %d\nTime to die %d\nTime to eat %d\nTime to sleep %d\nMeals per philo %d\n", ph.param.nb_philo, ph.param.time_to_die, ph.param.time_to_eat, ph.param.time_to_sleep, ph.param.meals_per_philo);
	return (0);
}