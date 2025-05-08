/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 06:24:14 by ipetrov           #+#    #+#             */
/*   Updated: 2025/05/08 11:59:41 by ipetrov          ###   ########.fr       */
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
		if (ctx->end == true)
			return (NULL);
		ctx->num_full_philos++;
		if (ctx->num_full_philos == ctx->num_philos)
		{
			printf("\nAll philos are full. Simulation is stopped.\n");
			clean_philos(ctx);
			return (NULL);
		}
		if (ft_sem_post(ctx->lock) != OK)
			return (NULL);
	}
	return (NULL);
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
		if (!ctx->end && (WEXITSTATUS(status) == DIED
				|| WEXITSTATUS(status) == ER))
			clean_philos(ctx);
	}
	if (ft_sem_post(ctx->full) != OK)
		return (ER);
	if (th_join(&tid) != OK)
		return (ER);
	return (OK);
}
