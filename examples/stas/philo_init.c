/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliashko <sliashko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:25:09 by sliashko          #+#    #+#             */
/*   Updated: 2024/02/07 17:58:13 by sliashko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo_data	**init_philos(int argc, char **argv, int *DEATH_FLAG)
{
	t_philo_data	**philos;
	int				n;
	int				i;

	n = ft_atoi(argv[1]);
	philos = (t_philo_data **) malloc(sizeof(t_philo_data *) * n);
	i = 0;
	while (i < n)
	{
		philos[i] = (t_philo_data *) malloc(sizeof(t_philo_data));
		philos[i]->time_to_die = ft_atoi(argv[2]) * 1000;
		philos[i]->time_to_eat = ft_atoi(argv[3]) * 1000;
		philos[i]->time_to_sleep = ft_atoi(argv[4]) * 1000;
		if (argc == 6)
			philos[i]->min_times_eat = ft_atoi(argv[5]);
		else
			philos[i]->min_times_eat = -1;
		philos[i]->pos = i;
		philos[i]->must_die = DEATH_FLAG;
		philos[i]->n = n;
		philos[i]->n_eats = 0;
		i++;
	}
	return (philos);
}

pthread_mutex_t	**init_forks(t_philo_data **philos)
{
	int				i;
	pthread_mutex_t	**forks;

	forks = (pthread_mutex_t **) malloc(sizeof(pthread_mutex_t *)
			* philos[0]->n);
	i = 0;
	while (i < philos[0]->n)
	{
		forks[i] = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(forks[i], NULL);
		i++;
	}
	return (forks);
}

void	assign_forks(t_philo_data	**philos, pthread_mutex_t	**forks)
{
	int	n;
	int	i;

	n = philos[0]->n;
	i = 1;
	philos[0]->left_fork = forks[0];
	philos[0]->right_fork = forks[n - 1];
	while (i < n)
	{
		philos[i]->left_fork = forks[i];
		philos[i]->right_fork = forks[i - 1];
		i++;
	}
}

void	create_mutexes(t_philo_data **philos)
{
	t_philo_muts	*muts;
	int				i;

	muts = (t_philo_muts *) malloc(sizeof(t_philo_muts));
	muts->exit_mut = malloc(sizeof(pthread_mutex_t));
	muts->print_mut = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(muts->exit_mut, NULL);
	pthread_mutex_init(muts->print_mut, NULL);
	i = 0;
	while (i < philos[0]->n)
	{
		philos[i]->muts = muts;
		i++;
	}
}
