/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 06:24:14 by ipetrov           #+#    #+#             */
/*   Updated: 2025/04/28 11:34:08 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_sts	death_monitor(t_ctx *ctx)
{
	t_int	i;
	t_time	now;

	if (smart_sleep(ctx->time_to_die, ctx) != OK)
		return (FAIL);
	while (true)
	{
		if (mtx_lock(&ctx->lock) != OK)
			return (FAIL);
		if (is_end(ctx)) //
			return (FAIL); // unlock mtx here
		if (get_time(MS, &now, ctx->start_time) != OK)
			return (FAIL); // unlock mtx here
		i = 0;
		while (i < ctx->num_philos)
		{
			if (is_dead(&ctx->philos[i], now))
			{
				printf("monitor found death\n");
				return (FAIL);
			}
			i++;
		}
		if (mtx_unlock(&ctx->lock) != OK)
			return (FAIL);
		if (smart_sleep(ctx->time_to_die, ctx) != OK)
			return (FAIL);
	}
}
