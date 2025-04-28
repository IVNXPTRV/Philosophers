/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 21:20:37 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/25 21:20:37 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->right_fork->mutex);
	pthread_mutex_unlock(&philo->left_fork->mutex);
}

static int	try_take_fork(t_philo *philo, t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	if (print_log_with_status_check(philo, FORK) == FAILURE)
	{
		pthread_mutex_unlock(&fork->mutex);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	try_take_forks(t_philo *philo)
{
	t_fork	*first_fork;
	t_fork	*second_fork;

	if (philo->id % 2)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	if (try_take_fork(philo, first_fork) == FAILURE)
		return (FAILURE);
	if (try_take_fork(philo, second_fork) == FAILURE)
	{
		pthread_mutex_unlock(&first_fork->mutex);
		return (FAILURE);
	}
	return (SUCCESS);
}
