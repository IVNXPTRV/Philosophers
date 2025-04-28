/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliashko <sliashko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:05:08 by sliashko          #+#    #+#             */
/*   Updated: 2024/02/07 17:52:05 by sliashko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_to_die(t_philo_data *philo)
{
	pthread_mutex_lock(philo->muts->exit_mut);
	if (*(philo->must_die))
	{
		pthread_mutex_unlock(philo->muts->exit_mut);
		return (TRUE);
	}
	else
	{
		pthread_mutex_unlock(philo->muts->exit_mut);
		return (FALSE);
	}
}

int	try_take_forks(t_philo_data *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (message("has taken a fork", get_curr_time(philo->start_time),
			philo->pos, philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (FALSE);
	}
	if (philo->n < 2)
		return (FALSE);
	pthread_mutex_lock(philo->right_fork);
	if (message("has taken a fork", get_curr_time(philo->start_time),
			philo->pos, philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		return (FALSE);
	}
	return (TRUE);
}

int	try_to_eat(t_philo_data *philo)
{
	if (message("is eating", get_curr_time(philo->start_time),
			philo->pos, philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (FALSE);
	}
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (TRUE);
}

void	*philo(void	*data)
{
	t_philo_data	*philo;

	philo = (t_philo_data *) data;
	if ((philo->pos % 2) == 0)
	{
		message(THNK, get_curr_time(philo->start_time), philo->pos, philo);
		ft_usleep((25000));
	}
	while (!(is_to_die(philo)))
	{
		if (!try_take_forks(philo))
			break ;
		gettimeofday(&philo->last_eat_time, NULL);
		pthread_mutex_lock(philo->muts->exit_mut);
		philo->n_eats++;
		pthread_mutex_unlock(philo->muts->exit_mut);
		if (!try_to_eat(philo))
			break ;
		if (message(SLEEP, get_curr_time(philo->start_time), philo->pos, philo))
			break ;
		ft_usleep(philo->time_to_sleep);
		if (message(THNK, get_curr_time(philo->start_time), philo->pos, philo))
			break ;
	}
	return (NULL);
}
