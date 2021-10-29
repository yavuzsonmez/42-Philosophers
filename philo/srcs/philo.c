/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 18:44:14 by ysonmez           #+#    #+#             */
/*   Updated: 2021/10/29 15:23:46 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*	Getting the parameters passed to the program */

size_t	parameters(char **argv, t_param *param)
{
	param->nb_philo = ft_atoi_ll(argv[1]);
	param->time_to_die = ft_atoi_ll(argv[2]);
	param->time_to_eat = ft_atoi_ll(argv[3]);
	param->time_to_sleep = ft_atoi_ll(argv[4]);
	if (argv[5] != NULL)
		param->meals_per_philo = ft_atoi_ll(argv[5]);
	if (param->nb_philo < 0 || param->nb_philo > 2147483647)
		return (1);
	else if (param->time_to_die < 0 || param->time_to_die > 2147483647)
		return (1);
	else if (param->time_to_eat < 0 || param->time_to_eat > 2147483647)
		return (1);
	else if (param->time_to_sleep < 0 || param->time_to_sleep > 2147483647)
		return (1);
	else if (argv[5] != NULL && (param->time_to_sleep < 0 || param->time_to_sleep > 2147483647))
		return (1);
	return (0);

}

void	*dinner()
{
	printf("Im am dining\n");
	return (NULL);
}

t_ph	*create_philo(t_param *param)
{
	int		i;
	t_ph	*philo;

	i = 0;
	philo = (t_ph *)malloc(sizeof(t_ph) * param->nb_philo);
	if (philo == NULL)
		return (NULL);
	while (i < param->nb_philo)
	{
		philo[i].i = i + 1;
		if(pthread_create(&philo[i].philosoph, NULL, &dinner, NULL))
			return (NULL);
		i++;
	}
	return (philo);
}

/*	Philosophers with THREADS & MUTEX */

int main(int argc, char **argv)
{
	t_param	param;
	t_ph	*philo;

	if (argc < 5 || argc > 6)
		return (1);
	if (parameters(argv, &param))
		return (1);
	philo = create_philo(&param);
	if (philo == NULL)
		return (1);
	/* Loop to create threads */
	printf("TEST!!\nNumber of philo %d\nTime to die %d\nTime to eat %d\nTime to sleep %d\nMeals per philo %d\n", param.nb_philo, param.time_to_die, param.time_to_eat, param.time_to_sleep, param.meals_per_philo);
	printf("END TEST PARAMETERS\n");
	int i = 0;
	while (i < param.nb_philo)
	{
		printf("philo numero %d UP\n", philo[i].i);
		i++;
	}
	free(philo);
	return (0);
}