/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 05:59:20 by ipetrov           #+#    #+#             */
/*   Updated: 2025/04/28 09:14:37 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_int	clean_ctx(t_ctx **ctx)
{
	mtx_destroy(&((*ctx)->lock));
	*ctx = NULL;
	return (OK);
}

t_int clean_forks(t_fork **forks)
{
	t_int	i;

	i = 0;
	while ((*forks)[i].id)
	{
		mtx_destroy(&(forks[i])->lock);
		i++;
	}
	free(*forks);
	*forks = NULL;
	return (OK);
}

// add mtx destroy
t_int clean_philos(t_philo **philos)
{
	// t_int	i;

	// i = 0;
	// while (*philos + i)
	// {
	// 	mtx_destroy(&(philos[i])->lock);
	// 	i++;
	// }
	free(*philos);
	*philos = NULL;
	return (OK);
}

t_sts join_threads(t_ctx *ctx)
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

// join threads
// cleans structs
t_sts clean(t_ctx *ctx)
{
	join_threads(ctx);
	clean_philos(&ctx->philos);
	clean_forks(&ctx->forks);
	clean_ctx(&ctx);
	return (OK);
}
