/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 04:21:35 by ipetrov           #+#    #+#             */
/*   Updated: 2025/05/09 09:32:32 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * @brief Allocate all philos, init all members except of ptid
 * 			Distribute forks properly
 *
 * @param ctx
 * @return int
 */
t_sts	allocate_philos(t_ctx *ctx)
{
	t_int	i;

	i = 0;
	while (i < ctx->num_philos)
	{
		ctx->philos[i].id = i + 1;
		ctx->philos[i].ctx = ctx;
		ctx->philos[i].last_meal_time = 0;
		if (ctx->meals_to_eat != -1)
			ctx->philos[i].meals_eaten = 0;
		i++;
	}
	return (OK);
}

t_sts	allocate_forks(t_ctx *ctx)
{
	if (ft_sem_open(&ctx->forks, FORKSNME, ctx->num_philos) != OK)
		return (ER);
	return (OK);
}

/**
 * @brief
 *
 * @param ctx
 * @return int
 */
t_sts	attach_philos(t_ctx *ctx)
{
	t_int	i;

	i = 0;
	if (get_time(MS, &ctx->start_time, EPOCH) != OK)
		return (ER);
	ctx->start_time += 80;
	while (i < ctx->num_philos)
	{
		if (ft_fork(&ctx->philos[i].pid) != OK)
			return (ER);
		if (ctx->philos[i].pid == 0)
			philo_routine(&ctx->philos[i]);
		i++;
	}
	return (OK);
}

/**
 * @brief
 * calculates time_to_think
 */
t_sts	init_ctx(t_ctx *ctx)
{
	mtx_init(&ctx->monitor_lock);
	if (ft_sem_open(&ctx->lock, LOCKNME, 1) != OK)
		return (ER);
	if (ft_sem_open(&ctx->full, FULLNME, 0) != OK)
	{
		clean_sem(LOCKNME, ctx->lock);
		return (ER);
	}
	if (ctx->num_philos % 2)
		ctx->time_to_think = 2 * ctx->time_to_eat - ctx->time_to_sleep;
	else
		ctx->time_to_think = ctx->time_to_eat - ctx->time_to_sleep;
	if (ctx->time_to_think < 0)
		ctx->time_to_think = 0;
	return (OK);
}

/*
 * Initializing main structures
 *
 */
t_sts	init_data(t_ctx *ctx)
{
	if (ft_sem_unlink(LOCKNME) != OK)
		return (ER);
	if (ft_sem_unlink(FORKSNME) != OK)
		return (ER);
	if (ft_sem_unlink(FULLNME) != OK)
		return (ER);
	if (init_ctx(ctx) != OK)
		return (ER);
	if (allocate_forks(ctx) != OK)
	{
		clean_sem(LOCKNME, ctx->lock);
		clean_sem(FULLNME, ctx->full);
		return (ER);
	}
	allocate_philos(ctx);
	if (attach_philos(ctx) != OK)
	{
		clean_philos(ctx);
		clean_sem(LOCKNME, ctx->lock);
		clean_sem(FULLNME, ctx->full);
		return (ER);
	}
	return (OK);
}
