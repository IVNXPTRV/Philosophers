/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 03:02:36 by ipetrov           #+#    #+#             */
/*   Updated: 2025/05/08 03:10:14 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

inline t_sts	check_in_meal(t_philo *philo, t_time now)
{
	philo->last_meal_time = now;
	philo->meals_eaten += 1;
	return (OK);
}

inline t_sts	is_all_full(t_philo *philo)
{
	if (philo->ctx->meals_to_eat == UNDEFINED)
		return (FALSE);
	if (philo->meals_eaten == philo->ctx->meals_to_eat)
	{
		philo->ctx->num_full_philos += 1;
		if (philo->ctx->num_full_philos == philo->ctx->num_philos)
		{
			philo->ctx->end = TRUE;
			printf("\nAll philos are full. Simulation is stopped.\n");
			mtx_unlock(&philo->ctx->lock);
			return (TRUE);
		}
	}
	return (FALSE);
}

t_sts	philo_eat(t_philo *philo)
{
	t_time	now;

	if (mtx_lock(&philo->ctx->lock) != OK)
		return (FAIL);
	if (get_time(MS, &now, philo->ctx->start_time) != OK)
		return (FAIL);
	if (is_end(philo->ctx))
		return (FAIL);
	if (is_dead(philo, now))
		return (FAIL);
	if (take_forks(philo, now) != OK)
		return (FAIL);
	check_in_meal(philo, now);
	if (putmsg(philo, now, EAT) != OK)
		return (FAIL);
	if (is_all_full(philo))
		return (FAIL);
	if (mtx_unlock(&philo->ctx->lock) != OK)
		return (FAIL);
	if (smart_sleep(philo->ctx->time_to_eat, philo->ctx) != OK)
		return (FAIL);
	if (release_forks(philo) != OK)
		return (FAIL);
	return (OK);
}
