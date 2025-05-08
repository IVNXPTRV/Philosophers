/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 03:02:36 by ipetrov           #+#    #+#             */
/*   Updated: 2025/05/08 06:55:02 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

inline t_sts	check_in_meal(t_philo *philo, t_time now)
{
	philo->last_meal_time = now;
	philo->meals_eaten += 1;
	return (OK);
}

inline t_sts	is_full(t_philo *philo)
{
	if (philo->ctx->meals_to_eat == UNDEFINED)
		return (FALSE);
	if (philo->meals_eaten == philo->ctx->meals_to_eat)
	{
		if (ft_sem_post(philo->ctx->full) != OK)
			return (ER);
	}
	return (FALSE);
}

t_sts	philo_eat(t_philo *philo)
{
	t_time	now;

	if (ft_sem_wait(philo->ctx->lock) != OK)
		return (FAIL);
	if (get_time(MS, &now, philo->ctx->start_time) != OK)
		return (FAIL);
	if (is_dead(philo, now))
		return (FAIL);
	if (take_forks(philo, now) != OK)
		return (FAIL);
	check_in_meal(philo, now);
	if (putmsg(philo, now, EAT) != OK)
		return (FAIL);
	if (is_full(philo))
		return (FAIL);
	if (ft_sem_post(philo->ctx->lock) != OK)
		return (FAIL);
	if (smart_sleep(philo->ctx->time_to_eat, philo) != OK)
		return (FAIL);
	if (release_forks(philo) != OK)
		return (FAIL);
	return (OK);
}
