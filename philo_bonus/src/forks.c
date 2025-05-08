/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 03:01:39 by ipetrov           #+#    #+#             */
/*   Updated: 2025/05/08 09:29:58 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static t_sts	take_fork(t_philo *philo)
{
	if (ft_sem_wait(philo->ctx->forks) != OK)
		return (ER);
	return (OK);
}

t_sts	take_forks(t_philo *philo)
{
	t_time	now;

	if (ft_sem_wait(philo->ctx->lock) != OK)
		return (FAIL);
	if (get_time(MS, &now, philo->ctx->start_time) != OK)
		return (FAIL);
	if (is_dead(philo, now))
		return (FAIL);
	if (take_fork(philo) != OK)
		return (FAIL);
	if (putmsg(philo, now, FORK_1) != OK)
		return (FAIL);
	if (philo->ctx->num_philos == 1)
	{
		if (ft_sem_post(philo->ctx->lock) != OK)
			return (FAIL);
		if (smart_sleep(philo->ctx->time_to_die + 1, philo) != OK)
			return (FAIL);
	}
	if (take_fork(philo) != OK)
		return (FAIL);
	if (putmsg(philo, now, FORK_2) != OK)
		return (FAIL);
	if (ft_sem_post(philo->ctx->lock) != OK)
		return (FAIL);
	usleep(1);
	return (OK);
}

static t_sts	release_fork(t_philo *philo)
{
	if (ft_sem_post(philo->ctx->forks) != OK)
		return (ER);
	return (OK);
}

t_sts	release_forks(t_philo *philo)
{
	if (release_fork(philo) != OK)
		return (FAIL);
	if (release_fork(philo) != OK)
		return (FAIL);
	return (OK);
}
