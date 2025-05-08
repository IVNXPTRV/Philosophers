/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 03:01:39 by ipetrov           #+#    #+#             */
/*   Updated: 2025/05/08 03:09:48 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static t_sts	take_fork(t_fork *fork)
{
	while (true)
	{
		if (mtx_lock(&fork->lock) != OK)
			return (FAIL);
		if (fork->state == false)
		{
			fork->state = true;
			if (mtx_unlock(&fork->lock) != OK)
				return (FAIL);
			return (OK);
		}
		if (mtx_unlock(&fork->lock) != OK)
			return (FAIL);
	}
}

t_sts	take_forks(t_philo *philo, t_time now)
{
	if (take_fork(philo->fork_one) != OK)
		return (FAIL);
	if (putmsg(philo, now, FORK_1) != OK)
		return (FAIL);
	if (philo->ctx->num_philos == 1)
	{
		if (mtx_unlock(&philo->ctx->lock) != OK)
			return (FAIL);
		if (smart_sleep(philo->ctx->time_to_die + 50, philo->ctx) != OK)
			return (FAIL);
		if (mtx_lock(&philo->ctx->lock) != OK)
			return (FAIL);
		if (is_end(philo->ctx))
			return (FAIL);
	}
	if (take_fork(philo->fork_two) != OK)
		return (FAIL);
	if (putmsg(philo, now, FORK_2) != OK)
		return (FAIL);
	return (OK);
}

static t_sts	release_fork(t_fork *fork)
{
	while (true)
	{
		if (mtx_lock(&fork->lock) != OK)
			return (FAIL);
		if (fork->state == true)
		{
			fork->state = false;
			if (mtx_unlock(&fork->lock) != OK)
				return (FAIL);
			return (OK);
		}
		if (mtx_unlock(&fork->lock) != OK)
			return (FAIL);
	}
	return (OK);
}

t_sts	release_forks(t_philo *philo)
{
	if (release_fork(philo->fork_one) != OK)
		return (FAIL);
	if (release_fork(philo->fork_two) != OK)
		return (FAIL);
	return (OK);
}
