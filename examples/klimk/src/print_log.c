/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:29:56 by dklimkin          #+#    #+#             */
/*   Updated: 2024/02/05 21:29:57 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_log(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->sim_log->mutex);
	printf("%011lld %d %s\n",
		(get_timestamp() - philo->sim_log->start_time), philo->id, message);
	pthread_mutex_unlock(&philo->sim_log->mutex);
	return (SUCCESS);
}

int	print_log_with_status_check(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->sim_log->mutex);
	pthread_mutex_lock(&philo->sim_status->mutex);
	if (philo->sim_status->should_stop == true)
	{
		pthread_mutex_unlock(&philo->sim_status->mutex);
		pthread_mutex_unlock(&philo->sim_log->mutex);
		return (FAILURE);
	}
	pthread_mutex_unlock(&philo->sim_status->mutex);
	printf("%011lld %d %s\n",
		(get_timestamp() - philo->sim_log->start_time), philo->id, message);
	pthread_mutex_unlock(&philo->sim_log->mutex);
	return (SUCCESS);
}
