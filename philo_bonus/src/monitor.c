/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 06:24:14 by ipetrov           #+#    #+#             */
/*   Updated: 2025/05/09 09:01:10 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	*full_monitor(void *ptr)
{
	t_ctx	*ctx;

	ctx = (t_ctx *)ptr;
	while (true)
	{
		if (ft_sem_wait(ctx->full) != OK)
			return (NULL);
		mtx_lock(&ctx->monitor_lock);
		if (ctx->end == true)
		{
			mtx_unlock(&ctx->monitor_lock);
			return (NULL);
		}
		mtx_unlock(&ctx->monitor_lock);
		ctx->num_full_philos++;
		if (ctx->num_full_philos == ctx->num_philos)
		{
			clean_philos(ctx);
			printf("\nAll philos are full. Simulation is stopped.\n");
			return (NULL);
		}
	}
	return (NULL);
}

t_sts	check_exit_sts(int *status, t_ctx *ctx)
{
	mtx_lock(&ctx->monitor_lock);
	if (ctx->end)
	{
		mtx_unlock(&ctx->monitor_lock);
		return (OK);
	}
	mtx_unlock(&ctx->monitor_lock);
	if ((WEXITSTATUS(*status) == DIED || WEXITSTATUS(*status) == ER))
		clean_philos(ctx);
	return (OK);
}

t_sts	end_monitor(t_ctx *ctx)
{
	int			status;
	int			code;
	pthread_t	tid;

	if (th_create(&tid, full_monitor, (void *)ctx) != OK)
		return (ER);
	while (true)
	{
		code = waitpid(ANYPID, &status, 0);
		if (code == ER)
		{
			if (errno == ECHILD)
				break ;
			return (puterr("waitpid: failed\n"));
		}
		check_exit_sts(&status, ctx);
	}
	if (ft_sem_post(ctx->full) != OK)
		return (ER);
	if (th_join(&tid) != OK)
		return (ER);
	return (OK);
}
