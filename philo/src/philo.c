/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 03:05:16 by ipetrov           #+#    #+#             */
/*   Updated: 2025/05/08 03:08:46 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static inline t_sts	stop_before_herd_gate(t_ctx *ctx)
{
	if (mtx_lock(&ctx->lock) != OK)
		return (FAIL);
	if (mtx_unlock(&ctx->lock) != OK)
		return (FAIL);
	return (OK);
}

t_sts	philo_delay(t_philo *philo)
{
	if (philo->id == philo->ctx->num_philos && philo->ctx->num_philos % 2
		&& philo->ctx->num_philos > 1)
	{
		if (smart_sleep(2 * philo->ctx->time_to_eat, philo->ctx) != OK)
			return (FAIL);
	}
	else
	{
		if (philo->id % 2 == 0)
		{
			if (smart_sleep(philo->ctx->time_to_eat, philo->ctx) != OK)
				return (FAIL);
		}
	}
	return (OK);
}

t_sts	philo_sleep(t_philo *philo)
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
	if (putmsg(philo, now, SLEEP) != OK)
		return (FAIL);
	if (mtx_unlock(&philo->ctx->lock) != OK)
		return (FAIL);
	if (smart_sleep(philo->ctx->time_to_sleep, philo->ctx) != OK)
		return (FAIL);
	return (OK);
}

t_sts	philo_think(t_philo *philo)
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
	if (putmsg(philo, now, THINK) != OK)
		return (FAIL);
	if (mtx_unlock(&philo->ctx->lock) != OK)
		return (FAIL);
	if (philo->ctx->time_to_think)
	{
		if (smart_sleep(philo->ctx->time_to_think, philo->ctx) != OK)
			return (FAIL);
	}
	return (OK);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;
	t_bool	end;

	philo = (t_philo *)ptr;
	end = false;
	if (stop_before_herd_gate(philo->ctx) != OK)
		end = true;
	if (!end && philo_delay(philo) != OK)
		end = true;
	while (!end)
	{
		if (philo_eat(philo) != OK)
			break ;
		if (philo_sleep(philo) != OK)
			break ;
		if (philo_think(philo) != OK)
			break ;
	}
	mtx_lock(&philo->ctx->lock);
	philo->ctx->end = TRUE;
	mtx_unlock(&philo->ctx->lock);
	return (NULL);
}
