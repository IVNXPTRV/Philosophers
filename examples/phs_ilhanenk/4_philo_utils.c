/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhanenk <ikhanenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:22:45 by ikhanenk          #+#    #+#             */
/*   Updated: 2025/04/04 13:22:45 by ikhanenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_find_forks(t_philo *ph)
{
	ph->rf = ph->nb;
	if (ph->rf != 0)
		ph->lf = ph->nb - 1;
	else if (ph->num_phs == 1)
		ph->lf = -1;
	else
		ph->lf = ph->num_phs - 1;
}

int	ft_check_fed_optional(t_philo *ph, int num_phs, int add)
{
	int	i;
	int	fed_phs;

	pthread_mutex_lock(&ph->params->fed_lock);
	fed_phs = 0;
	if (add == 1)
		ph->meals_num[ph->nb] += 1;
	i = -1;
	while (++i < num_phs)
	{
		if (ph->meals_num[i] == ph->num_eat)
			fed_phs++;
	}
	if (fed_phs >= num_phs)
	{
		pthread_mutex_unlock(&ph->params->fed_lock);
		return (1);
	}
	pthread_mutex_unlock(&ph->params->fed_lock);
	return (0);
}

void	ft_ph_eat(t_philo *ph)
{
	ft_find_forks(ph);
	if (ph->lf == -1 || ph->rf == -1)
	{
		if (ph->lf != -1)
			pthread_mutex_lock(&ph->f_m[ph->lf]);
		if (ph->rf != -1)
			pthread_mutex_lock(&ph->f_m[ph->rf]);
		ft_print_message(ph, ph->nb, FORK, 0);
		usleep(ph->to_die * 1000);
		if (ph->lf != -1)
			pthread_mutex_unlock(&ph->f_m[ph->lf]);
		if (ph->rf != -1)
			pthread_mutex_unlock(&ph->f_m[ph->rf]);
		return ;
	}
	if (ph->nb % 2 == 0 && (ph->nb != ph->num_phs - 1))
		ft_mute_forks_even(ph);
	ft_ts_first_queue(ph);
	if (ph->nb % 2 != 0)
		ft_mute_forks_odd(ph);
	ft_ts_second_queue(ph);
	if (ph->num_phs % 2 == 1)
		ft_for_odd_number(ph);
}
