/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 06:24:14 by ipetrov           #+#    #+#             */
/*   Updated: 2025/05/08 07:46:06 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void *full_monitor(void *ptr)
{
	t_ctx *ctx;

	ctx = (t_ctx *)ptr;
	while (true)
	{
		if (ft_sem_wait(ctx->full) != OK)
			return (NULL);
		ctx->num_full_philos++;
		if (ctx->num_full_philos == ctx->num_philos)
		{
			//print everyone is full here
			clean_philos(ctx); //kill all processes
			return (NULL);
		}
		if (ft_sem_post(ctx->lock) != OK) // continue simulation after check
			return (NULL);
	}
	return (NULL);
}

t_sts	end_monitor(t_ctx *ctx)
{
	int status;
	int	code;
	pthread_t tid;

	if (th_create(&tid, full_monitor, (void *)ctx) != OK)
		return (ER);
	pthread_detach(tid); // make error wrapper
	while (true)
	{
		code = waitpid(ANYPID, &status, 0);
		if (code == ER) // blocks parent until any child send sighild
		{
			if (errno == ECHILD) // all children collected
				break ;
			return (puterr("waitpid: failed\n"));
		}
		if (WEXITSTATUS(status) == DIED)
		{
			clean_philos(ctx); //kill all processes
			break ;
		}
		else if (WEXITSTATUS(status) == ER)
		{
			clean_philos(ctx); //kill all processes
			break ;
		}
		if (ft_sem_post(ctx->lock) != OK) // continue simulation after check
			return (ER);
	}
	return (OK);
}
