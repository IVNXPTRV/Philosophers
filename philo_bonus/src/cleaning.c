/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 05:59:20 by ipetrov           #+#    #+#             */
/*   Updated: 2025/05/08 17:04:12 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_int	clean_sem(char *name, sem_t *sem)
{
	ft_sem_close(sem);
	ft_sem_unlink(name);
	return (OK);
}

t_int	clean_philos(t_ctx *ctx)
{
	t_int	i;

	i = 0;
	while (i < ctx->num_philos)
	{
		if (ctx->philos[i].pid != 0)
			kill(ctx->philos[i].pid, SIGKILL);
		i++;
	}
	return (OK);
}

t_sts	clean(t_ctx *ctx)
{
	clean_sem(LOCKNME, ctx->lock);
	clean_sem(FORKSNME, ctx->forks);
	clean_sem(FULLNME, ctx->full);
	return (OK);
}
