/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 04:21:35 by ipetrov           #+#    #+#             */
/*   Updated: 2025/04/16 12:58:27 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"



/**
 * @brief Allocate all philos, init all members except of ptid
 * 		  Distribute forks properly
 *
 * @param ctx
 * @return int
 */
int	allocate_philos(t_ctx *ctx)
{
	int32_t	i;

	ctx->philos = ft_calloc(ctx->nbr_philos + 1, sizeof(t_philo));
	if (!ctx->philos)
		return (ERROR);
	i = 0;
	while (i < ctx->nbr_philos)
	{
		ctx->philos[i].id = i + 1;
		ctx->philos[i].ctx = ctx;
		if (ctx->philos[i].id < ctx->nbr_philos - 1)
		{
			ctx->philos[i].first_fork = &ctx->forks[i];
			ctx->philos[i].second_fork = &ctx->forks[i + 1];
		}
		else
		{
			ctx->philos[i].first_fork = &ctx->forks[0];
			ctx->philos[i].second_fork = &ctx->forks[i + 1];
		}
		ctx->philos[i].meals_to_eat = ctx->philos_full;
		i++;
	}
	return (SUCCESS);
}

int	allocate_forks(t_ctx *ctx)
{
	int32_t	i;

	ctx->forks = ft_calloc(ctx->nbr_philos + 1, sizeof(t_fork));
	if (!ctx->forks)
		return (ERROR);
	i = 0;
	while (i < ctx->nbr_philos)
	{
		ctx->forks[i].id = i + 1;
		if (mtx_init(&ctx->forks[i].lock) != SUCCESS)
		{
			clean_forks(&ctx->forks);
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}


/**
 * @brief
 *
 * @param ctx
 * @return int
 */
int	attach_philos(t_ctx *ctx)
{
	int32_t	i;

	i = 0;
	while (i < ctx->nbr_philos)
	{
		if (th_create(&ctx->philos[i].tid, philo_routine, &ctx->philos[i]) != SUCCESS)
			return (ERROR); // some shut down mutex force all threads wait util main thread clean eveything and exit
		i++;
	}
	return (SUCCESS);
}

/**
 * @brief
 *
 * @return int
 */
int	init_ctx(t_ctx *ctx)
{
	if (mtx_init(&ctx->lock) != SUCCESS)
		return (ERROR);
	ctx->status = WAIT;
	return (SUCCESS);
}

/*
 * Initializing main structures
 *
*/
int	init_data(t_ctx *ctx)
{
	if (init_ctx(ctx) != SUCCESS)
		return (ERROR);
	if (allocate_forks(ctx) != SUCCESS)
	{
		clean_ctx(&ctx);
		return (ERROR);
	}
	if (allocate_philos(ctx) != SUCCESS)
	{
		clean_forks(&ctx->forks);
		clean_ctx(&ctx);
		return (ERROR);
	}
	if (attach_philos(ctx) != SUCCESS)
	{
		clean_philos(&ctx->philos);
		clean_forks(&ctx->forks);
		clean_ctx(&ctx);
		return (ERROR);
	}
	if (ctx->philos_full != -1)
		ctx->philos_full = 0;
	return (SUCCESS);
}
