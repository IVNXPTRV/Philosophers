/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliashko <sliashko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:32:59 by sliashko          #+#    #+#             */
/*   Updated: 2024/02/07 17:25:06 by sliashko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_number(char *s)
{
	while (*s)
	{
		if (!(*s >= '0' && *s <= '9'))
			return (FALSE);
		s++;
	}
	return (TRUE);
}

int	validate_params(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		write(2, "Incorrect number of parameters\n", 31);
		return (TRUE);
	}
	if (!(is_number(argv[1]) && is_number(argv[2])
			&& is_number(argv[3]) && is_number(argv[4])))
	{
		write(2, "All params must be numbers\n", 28);
		return (TRUE);
	}
	if (ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60
		|| ft_atoi(argv[4]) < 60)
	{
		write(2, "Time params must not be smaller than 60ms\n", 42);
		return (TRUE);
	}
	return (FALSE);
}

void	launch_philos(t_philo_data **philos, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < philos[0]->n)
	{
		pthread_create(&threads[i], NULL, &philo, philos[i]);
		i++;
	}
}

void	join_threads(pthread_t *threads, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

int	main(int argc, char	**argv)
{
	int				dead_flag;
	t_philo_data	**philos;
	pthread_mutex_t	**forks;
	pthread_t		*threads;
	pthread_t		checker;

	if (validate_params(argc, argv))
		return (EXIT_FAILURE);
	dead_flag = FALSE;
	threads = (pthread_t *) malloc(sizeof(pthread_t) * ft_atoi(argv[1]));
	philos = init_philos(argc, argv, &dead_flag);
	forks = init_forks(philos);
	assign_forks(philos, forks);
	create_mutexes(philos);
	set_start_time(philos, philos[0]->n);
	launch_philos(philos, threads);
	pthread_create(&checker, NULL, &death_checker, philos);
	join_threads(threads, philos[0]->n);
	pthread_join(checker, NULL);
	free(threads);
	free_muts(philos[0]);
	free_philos(philos);
	free_forks(forks, philos[0]->n);
	return (EXIT_SUCCESS);
}
