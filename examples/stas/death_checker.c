/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliashko <sliashko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:42:48 by sliashko          #+#    #+#             */
/*   Updated: 2024/02/07 17:39:04 by sliashko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_all_eaten(t_philo_data **philos)
{
	int	i;

	if (philos[0]->min_times_eat == -1)
		return (FALSE);
	i = 0;
	while (i < philos[0]->n)
	{
		pthread_mutex_lock(philos[i]->muts->exit_mut);
		if (philos[i]->n_eats < philos[i]->min_times_eat)
		{
			pthread_mutex_unlock(philos[i]->muts->exit_mut);
			return (FALSE);
		}
		pthread_mutex_unlock(philos[i]->muts->exit_mut);
		i++;
	}
	return (TRUE);
}

void	set_die_flag(t_philo_data *philo)
{
	pthread_mutex_lock(philo->muts->exit_mut);
	*(philo->must_die) = TRUE;
	pthread_mutex_unlock(philo->muts->exit_mut);
}

int	check_death(t_philo_data *philo, struct timeval curr_time)
{
	return ((1000000 * (curr_time.tv_sec - philo->last_eat_time.tv_sec)
			+ (curr_time.tv_usec
				- philo->last_eat_time.tv_usec - 100))
		> philo->time_to_die);
}

int	is_any_dead(t_philo_data **philos)
{
	int				i;
	struct timeval	curr_time;

	i = 0;
	while (i < philos[0]->n)
	{
		gettimeofday(&curr_time, NULL);
		if (check_death(philos[i], curr_time))
		{
			set_die_flag(philos[i]);
			printf("%ld %d died\n", get_curr_time(philos[i]->start_time),
				philos[i]->pos);
			return (TRUE);
		}
		if (is_all_eaten(philos))
		{
			set_die_flag(philos[i]);
			printf("%ld All philos have eaten at least %d times\n",
				get_curr_time(philos[i]->start_time), philos[0]->min_times_eat);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

void	*death_checker(void	*philos_arr)
{
	t_philo_data	**philos;

	philos = (t_philo_data **) philos_arr;
	while (!(is_any_dead(philos)))
		ft_usleep(10);
	return (NULL);
}
