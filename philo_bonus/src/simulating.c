/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulating.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 07:36:45 by ipetrov           #+#    #+#             */
/*   Updated: 2025/05/08 03:10:07 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

inline t_sts	is_end(t_ctx *ctx)
{
	if (ctx->end)
	{
		mtx_unlock(&ctx->lock);
		return (TRUE);
	}
	return (FALSE);
}

t_sts	is_dead(t_philo *philo, t_time now)
{
	if (now - philo->last_meal_time > philo->ctx->time_to_die)
	{
		philo->ctx->end = TRUE;
		putmsg(philo, now, DIED);
		printf("\nOne philo is dead. Simulation is stopped.\n");
		mtx_unlock(&philo->ctx->lock);
		return (TRUE);
	}
	else
		return (FALSE);
}

inline t_sts	open_herd_gate(t_ctx *ctx)
{
	if (mtx_unlock(&ctx->lock) != OK)
		return (ER);
	return (OK);
}

inline t_sts	init_start_time(t_ctx *ctx)
{
	if (get_time(MS, &ctx->start_time, EPOCH) != OK)
		return (ER);
	return (OK);
}

/**
 * @brief
 * timestamp_in_ms X is thinking
 * timestamp_in_ms X has taken a fork
 * timestamp_in_ms X has taken a fork
 * timestamp_in_ms X is eating
 * timestamp_in_ms X is sleeping
 * timestamp_in_ms X died
 */
t_sts	run_simulation(t_ctx *ctx)
{
	if (init_start_time(ctx) != OK)
		return (FAIL);
	if (open_herd_gate(ctx) != OK)
		return (FAIL);
	death_monitor(ctx);
	mtx_lock(&ctx->lock);
	ctx->end = TRUE;
	mtx_unlock(&ctx->lock);
	return (OK);
}
