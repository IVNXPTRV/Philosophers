/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 05:59:20 by ipetrov           #+#    #+#             */
/*   Updated: 2025/04/24 02:23:04 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	clean_ctx(t_ctx **ctx)
{
	mtx_destroy(&(*ctx)->lock);
	*ctx = NULL;
	return (SUCCESS);
}

int clean_forks(t_fork **forks)
{
	int64_t	i;

	i = 0;
	while ((*forks)[i].id)
	{
		mtx_destroy(&(forks[i])->lock);
		i++;
	}
	free(*forks);
	*forks = NULL;
	return (SUCCESS);
}

// add mtx destroy
int clean_philos(t_philo **philos)
{
	// int64_t	i;

	// i = 0;
	// while (*philos + i)
	// {
	// 	mtx_destroy(&(philos[i])->lock);
	// 	i++;
	// }
	free(*philos);
	*philos = NULL;
	return (SUCCESS);
}

int clean(t_ctx *ctx)
{
	clean_philos(&ctx->philos);
	clean_forks(&ctx->forks);
	clean_ctx(&ctx);
	return (SUCCESS);
}
