/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:31:27 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/24 15:31:28 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_forks(t_sim **sim)
{
	int		i;

	(*sim)->forks = (t_fork *)malloc((
				(*sim)->params.number_of_philos) * sizeof(t_fork));
	if (!(*sim)->forks)
		return (ERROR);
	memset((*sim)->forks, 0, (*sim)->params.number_of_philos * sizeof(t_fork));
	i = 0;
	while (i < (*sim)->params.number_of_philos)
	{
		if (pthread_mutex_init(&(*sim)->forks[i].mutex, NULL) != SUCCESS)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

static int	create_meal(t_meal **meal, int number_of_meals, int count)
{
	(*meal) = (t_meal *)malloc(count * sizeof(t_meal));
	if (!(*meal))
		return (ERROR);
	memset((*meal), 0, count * sizeof(t_meal));
	if (pthread_mutex_init(&(*meal)->mutex, NULL) != SUCCESS)
		return (ERROR);
	(*meal)->number_of_meals_left = number_of_meals;
	return (SUCCESS);
}

static int	create_philosophers(t_sim **sim)
{
	int		i;

	(*sim)->philos = (t_philo *)malloc(
			(*sim)->params.number_of_philos * sizeof(t_philo));
	if (!(*sim)->philos)
		return (ERROR);
	memset((*sim)->philos, 0,
		((*sim)->params.number_of_philos * sizeof(t_philo)));
	i = 0;
	while (i < (*sim)->params.number_of_philos)
	{
		(*sim)->philos[i].id = (i + 1);
		(*sim)->philos[i].sim_params = (*sim)->params;
		(*sim)->philos[i].sim_status = &(*sim)->status;
		(*sim)->philos[i].sim_log = &(*sim)->log;
		(*sim)->philos[i].left_fork = &((*sim)->forks[i]);
		(*sim)->philos[i].right_fork = &((*sim)->forks[(
					(i + 1) % (*sim)->params.number_of_philos)]);
		if (create_meal(&(*sim)->philos[i].meal, (*sim)->params.number_of_meals,
				(*sim)->params.number_of_philos) != SUCCESS)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

int	init_sim(t_sim **sim, t_sim_params params)
{
	(*sim)->params = params;
	memset(&(*sim)->status, 0, sizeof(t_sim_status));
	if (pthread_mutex_init(&(*sim)->status.mutex, NULL) != SUCCESS)
		return (ERROR);
	if (pthread_mutex_init(&(*sim)->log.mutex, NULL) != SUCCESS)
		return (ERROR);
	if (create_forks(sim) == ERROR)
		return (ERROR);
	if (create_philosophers(sim) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
