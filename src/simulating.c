/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulating.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 07:36:45 by ipetrov           #+#    #+#             */
/*   Updated: 2025/04/16 10:01:40 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int wait_simulation_begin(t_ctx *ctx)
{
	int32_t	status;

	status = true;
	while (status)
	{
		if (get_val(&ctx->lock, &ctx->status, &status, sizeof(int32_t)) != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (wait_simulation_begin(philo->ctx) != SUCCESS)
	{
		set_val(&philo->ctx->lock, &philo->ctx->status, &(int32_t){ERROR}, sizeof(int32_t));
		return ((void *)ERROR);
	}
	return ((void *)SUCCESS);
}

int run_simulation(t_ctx *ctx)
{
	if (set_val(&ctx->lock, &ctx->status, &(int32_t){0}, sizeof(int32_t)) != SUCCESS)
		retunr (ERROR);

}
