/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 05:59:20 by ipetrov           #+#    #+#             */
/*   Updated: 2025/04/24 13:05:21 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	clean_ctx(t_ctx **ctx)
{
	mtx_destroy(&(*ctx)->lock);
	*ctx = NULL;
	return (OK);
}

int clean_forks(t_fork **forks)
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
int clean_philos(t_philo **philos)
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

int clean(t_ctx *ctx)
{
	clean_philos(&ctx->philos);
	clean_forks(&ctx->forks);
	clean_ctx(&ctx);
	return (OK);
}
