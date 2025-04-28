/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 20:24:50 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/25 20:24:51 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	try_eat(t_philo *philo)
{
	if (try_take_forks(philo) == FAILURE)
		return (FAILURE);
	if (print_log_with_status_check(philo, EAT) == FAILURE)
	{
		release_forks(philo);
		return (FAILURE);
	}
	pthread_mutex_lock(&philo->meal->mutex);
	philo->meal->last_meal = get_timestamp();
	if (philo->meal->number_of_meals_left != UNSPECIFIED)
		philo->meal->number_of_meals_left--;
	pthread_mutex_unlock(&philo->meal->mutex);
	smart_usleep(philo->sim_params.time_to_eat * US_PER_MS);
	release_forks(philo);
	return (SUCCESS);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	print_log(philo, THINK);
	if (philo->sim_start_delay > 0)
		smart_usleep(philo->sim_start_delay * US_PER_MS);
	while (1)
	{
		if (try_eat(philo) == FAILURE)
			return (NULL);
		if (print_log_with_status_check(philo, SLEEP) == FAILURE)
			return (NULL);
		smart_usleep(philo->sim_params.time_to_sleep * US_PER_MS);
		if (print_log_with_status_check(philo, THINK) == FAILURE)
			return (NULL);
	}
}
