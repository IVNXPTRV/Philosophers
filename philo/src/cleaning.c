/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 05:59:20 by ipetrov           #+#    #+#             */
/*   Updated: 2025/04/28 10:53:56 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_int	clean_ctx(t_ctx **ctx)
{
	mtx_destroy(&((*ctx)->lock));
	*ctx = NULL;
	return (OK);
}

t_int	clean_forks(t_ctx *ctx)
{
	t_int	i;

	i = 0;
	while (ctx->forks[i].id < ctx->num_philos)
	{
		mtx_destroy(&ctx->forks[i].lock);
		i++;
	}
	free(ctx->forks);
	ctx->forks = NULL;
	return (OK);
}

t_int	clean_philos(t_philo **philos)
{
	free(*philos);
	*philos = NULL;
	return (OK);
}

t_sts	join_threads(t_ctx *ctx)
{
	t_int	i;

	i = 0;
	while (i < ctx->num_philos)
	{
		th_join(&ctx->philos[i].tid);
		i++;
	}
	return (OK);
}

t_sts	clean(t_ctx *ctx)
{
	join_threads(ctx);
	clean_philos(&ctx->philos);
	clean_forks(ctx);
	clean_ctx(&ctx);
	return (OK);
}
