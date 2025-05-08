/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 05:59:20 by ipetrov           #+#    #+#             */
/*   Updated: 2025/05/08 07:46:19 by ipetrov          ###   ########.fr       */
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

// t_sts	clean(t_ctx *ctx)
// {
// 	clean_philos(&ctx->philos);
// 	clean_forks(ctx);
// 	clean_ctx(&ctx);
// 	return (OK);
// }
