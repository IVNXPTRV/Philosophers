/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_philo_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:02:14 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/31 14:02:16 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_philo_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal->mutex);
	if (get_timestamp() - philo->meal->last_meal
		>= (philo->sim_params.time_to_die))
	{
		pthread_mutex_unlock(&philo->meal->mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->meal->mutex);
	return (false);
}

bool	has_philo_meals_left(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal->mutex);
	if (philo->meal->number_of_meals_left != UNSPECIFIED)
	{
		if (philo->meal->number_of_meals_left <= 0)
		{
			pthread_mutex_unlock(&philo->meal->mutex);
			return (true);
		}
	}
	pthread_mutex_unlock(&philo->meal->mutex);
	return (false);
}
