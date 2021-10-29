/* TEST */

	printf("TEST!!\nNumber of philo %d\nTime to die %d\nTime to eat %d\nTime to sleep %d\nMeals per philo %d\n", param.nb_philo, param.time_to_die, param.time_to_eat, param.time_to_sleep, param.meals_per_philo);
	printf("END TEST PARAMETERS\n");
	int i = 0;
	while (i < param.nb_philo)
	{
		printf("philo numero %d UP\n", philo[i].i);
		i++;
	}
/* END TEST */