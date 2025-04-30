/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhanenk <ikhanenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 21:37:10 by ikhanenk          #+#    #+#             */
/*   Updated: 2025/04/07 21:37:10 by ikhanenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_print_message(t_philo *ph, int nb, int status, int change)
{
	long	time;

	pthread_mutex_lock(&ph->params->print_lock);
	time = ft_get_time() - ph->start;
	if (check_death_or_fed(ph, change) == 0)
	{
		if (status == FORK)
			printf(WHITE"%ld ms %d has taken a fork\n", time, nb + 1);
		if (status == EAT)
			printf(WHITE"%ld ms %d is eating\n\n", time, nb + 1);
		if (status == THINK)
			printf(BLUE"%ld ms %d is thinking\n\n", time, nb + 1);
		if (status == SLEEP)
			printf(SKY_BLUE"%ld ms %d is sleeping\n\n", time, nb + 1);
		pthread_mutex_unlock(&ph->params->print_lock);
		return (0);
	}
	if (status == DIE)
		printf(RED"%ld ms %d died\n\n"DFT, time, nb + 1);
	if (status == FED)
		printf(RED"All philosphers have eaten enough\n");
	pthread_mutex_unlock(&ph->params->print_lock);
	return (1);
}

long	check_time(t_philo *ph, int n)
{
	long	time;

	time = 0;
	pthread_mutex_lock(&ph->params->time_lock);
	if (n == 0)
		time = ph->last_eating;
	else if (n == 1)
		ph->last_eating = ft_get_time();
	pthread_mutex_unlock(&ph->params->time_lock);
	return (time);
}

int	check_death_or_fed(t_philo *ph, int change)
{
	int	i;

	i = 0;
	if (change == 1 && ph->params->death_or_fed == 0)
	{
		ph->params->death_or_fed = 1;
		return (1);
	}
	if (change == 0)
		i = ph->params->death_or_fed;
	return (i);
}
