/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliashko <sliashko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:33:09 by sliashko          #+#    #+#             */
/*   Updated: 2024/02/07 17:45:25 by sliashko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	message(char *msg, long time, int pos, t_philo_data *philo)
{
	pthread_mutex_lock(philo->muts->print_mut);
	if (is_to_die(philo))
	{
		pthread_mutex_unlock(philo->muts->print_mut);
		return (TRUE);
	}
	printf("%ld %d %s\n", time, pos, msg);
	pthread_mutex_unlock(philo->muts->print_mut);
	return (FALSE);
}

void	set_start_time(t_philo_data **philos, int n)
{
	int				i;
	struct timeval	start_time;

	i = 0;
	gettimeofday(&start_time, NULL);
	while (i < n)
	{
		philos[i]->start_time = start_time;
		philos[i]->last_eat_time = start_time;
		i++;
	}
}

long	get_curr_time(struct timeval start_time)
{
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	return ((curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000)
		- (start_time.tv_sec * 1000 + start_time.tv_usec / 1000));
}

void	ft_usleep(long time_usec)
{
	struct timeval	start_time;
	struct timeval	curr_time;

	gettimeofday(&start_time, NULL);
	gettimeofday(&curr_time, NULL);
	while ((1000000 * (curr_time.tv_sec - start_time.tv_sec)
			+ (curr_time.tv_usec - start_time.tv_usec)) <= time_usec)
	{
		usleep(200);
		gettimeofday(&curr_time, NULL);
	}
}
