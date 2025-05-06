/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 04:21:35 by ipetrov           #+#    #+#             */
/*   Updated: 2025/04/28 10:25:08 by ipetrov          ###   ########.fr       */
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

	ctx->philos = ft_calloc(ctx->num_philos, sizeof(t_philo));
	if (!ctx->philos)
		return (ER);
	i = 0;
	while (i < ctx->num_philos)
	{
		ctx->philos[i].id = i + 1;
		ctx->philos[i].ctx = ctx;
		if (ctx->philos[i].id < ctx->num_philos)
		{
			ctx->philos[i].fork_one = &ctx->forks[i];
			ctx->philos[i].fork_two = &ctx->forks[i + 1];
		}
		else
		{
			ctx->philos[i].fork_one = &ctx->forks[0];
			ctx->philos[i].fork_two = &ctx->forks[i];
		}
		i++;
	}
	return (OK);
}

t_sts	allocate_forks(t_ctx *ctx)
{
	t_int	i;

	ctx->forks = ft_calloc(ctx->num_philos, sizeof(t_fork));
	if (!ctx->forks)
		return (ER);
	i = 0;
	while (i < ctx->num_philos)
	{
		ctx->forks[i].id = i + 1;
		ctx->forks[i].state = false;
		if (mtx_init(&ctx->forks[i].lock) != OK)
		{
			clean_forks(ctx);
			return (ER);
		}
		i++;
	}
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
	while (i < ctx->num_philos)
	{
		if (th_create(&ctx->philos[i].tid, philo_routine,
				&ctx->philos[i]) != OK)
			return (ER);
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
	if (mtx_init(&ctx->lock) != OK)
		return (ER);
	if (mtx_lock(&ctx->lock) != OK)
		return (ER);
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
	if (init_ctx(ctx) != OK)
		return (ER);
	if (allocate_forks(ctx) != OK)
	{
		mtx_unlock(&ctx->lock);
		clean_ctx(&ctx);
		return (ER);
	}
	if (allocate_philos(ctx) != OK)
	{
		mtx_unlock(&ctx->lock);
		clean_forks(ctx);
		clean_ctx(&ctx);
		return (ER);
	}
	if (attach_philos(ctx) != OK)
	{
		mtx_unlock(&ctx->lock);
		clean_philos(&ctx->philos);
		clean_forks(ctx);
		clean_ctx(&ctx);
		return (ER);
	}
	return (OK);
}
