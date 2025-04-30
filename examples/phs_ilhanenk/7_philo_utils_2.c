/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_philo_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhanenk <ikhanenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:51:21 by ikhanenk          #+#    #+#             */
/*   Updated: 2025/04/22 21:07:09 by ikhanenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_start_threads(t_philo *ph)
{
	int				i;

	if (pthread_create(&ph->params->check_phs_died, NULL, ft_check_death, ph))
		return (perror("Error "));
	i = -1;
	while (++i < ph->params->num_phs)
	{
		if (pthread_create(&(ph[i].thread), NULL, ft_dinner, ph + i))
			return (perror("Error "));
	}
}

void	ft_join_threads(t_philo *ph)
{
	int		i;

	i = -1;
	while (++i < ph->num_phs)
	{
		if (pthread_join(ph[i].thread, NULL) != 0)
			return (perror("Error "));
	}
	if (pthread_join(ph->params->check_phs_died, NULL) != 0)
		return (perror("Error "));
}

long	ft_get_time(void)
{
	struct timeval	tmp_time;
	long			milisec;

	gettimeofday(&tmp_time, NULL);
	milisec = tmp_time.tv_sec * 1000;
	milisec += tmp_time.tv_usec / 1000;
	return (milisec);
}

void	ft_cleaner(t_philo *ph)
{
	int		i;

	i = -1;
	while (++i < ph->params->num_phs)
	{
		pthread_mutex_destroy(&ph->params->f_m[i]);
		pthread_mutex_destroy(&(ph + i)->th_time_lock);
	}
	pthread_mutex_destroy(&ph->params->fed_lock);
	pthread_mutex_destroy(&ph->params->time_lock);
	pthread_mutex_destroy(&ph->params->print_lock);
	free(ph->params->f_m);
	free(ph->meals_num);
	free(ph);
}
