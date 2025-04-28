/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:17:26 by dklimkin          #+#    #+#             */
/*   Updated: 2024/02/06 17:17:27 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_threads(t_sim **sim)
{
	int	i;

	i = 0;
	while (i < (*sim)->params.number_of_philos)
	{
		pthread_join((*sim)->threads[i], NULL);
		i++;
	}
}

static int	create_even_threads(t_sim **sim, int start_index)
{
	while (start_index < (*sim)->params.number_of_philos)
	{
		(*sim)->philos[start_index].meal->last_meal = (*sim)->log.start_time;
		if (pthread_create(&(*sim)->threads[start_index], NULL,
				philo_routine, &(*sim)->philos[start_index]) != SUCCESS)
			return (ERROR);
		start_index += 2;
		usleep(10);
	}
	return (SUCCESS);
}

static int	create_odd_threads(t_sim **sim)
{
	int	start_delay;
	int	i;

	start_delay = 0;
	i = 0;
	while (i < (*sim)->params.number_of_philos)
	{
		(*sim)->philos[i].meal->last_meal = (*sim)->log.start_time;
		if ((*sim)->params.number_of_philos % 2 != 0)
			start_delay = (i % 10) * 5;
		(*sim)->philos[i].sim_start_delay = start_delay;
		if (pthread_create(&(*sim)->threads[i], NULL,
				philo_routine, &(*sim)->philos[i]) != SUCCESS)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

int	create_threads(t_sim **sim)
{
	(*sim)->threads = (pthread_t *)malloc(
			(*sim)->params.number_of_philos * sizeof(pthread_t));
	if (!(*sim)->threads)
		return (ERROR);
	(*sim)->log.start_time = get_timestamp();
	if ((*sim)->params.number_of_philos % 2 == 0)
	{
		if (create_even_threads(sim, 0) != SUCCESS)
			return (ERROR);
		if (create_even_threads(sim, 1) != SUCCESS)
			return (ERROR);
	}
	else
	{
		if (create_odd_threads(sim) != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}
