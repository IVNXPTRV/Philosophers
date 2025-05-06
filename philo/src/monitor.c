/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 06:24:14 by ipetrov           #+#    #+#             */
/*   Updated: 2025/04/30 09:31:30 by ipetrov          ###   ########.fr       */
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
		if (is_end(ctx))
			return (FAIL);
		if (get_time(MS, &now, ctx->start_time) != OK)
			return (FAIL);
		i = 0;
		while (i < ctx->num_philos)
		{
			if (is_dead(&ctx->philos[i], now))
				return (FAIL);
			i++;
		}
		if (mtx_unlock(&ctx->lock) != OK)
			return (FAIL);
		if (usleep(7000) == ER)
			return (puterr("usleep: Error: Interrupted system call\n"));
	}
}
