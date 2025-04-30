/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_philo_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhanenk <ikhanenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:58:21 by ikhanenk          #+#    #+#             */
/*   Updated: 2025/04/25 17:34:44 by ikhanenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	ft_mute_forks_odd(t_philo *ph)
{
	pthread_mutex_lock(&ph->f_m[ph->rf]);
	ft_print_message(ph, ph->nb, FORK, 0);
	pthread_mutex_lock(&ph->f_m[ph->lf]);
	ft_print_message(ph, ph->nb, FORK, 0);
	ft_print_message(ph, ph->nb, EAT, 0);
	usleep(ph->to_eat * 1000);
	if (ph->num_eat != -1)
		ft_check_fed_optional(ph, ph->num_phs, 1);
	check_time(ph, 1);
	pthread_mutex_unlock(&ph->f_m[ph->rf]);
	pthread_mutex_unlock(&ph->f_m[ph->lf]);
}

void	ft_mute_forks_even(t_philo *ph)
{
	pthread_mutex_lock(&ph->f_m[ph->lf]);
	ft_print_message(ph, ph->nb, FORK, 0);
	pthread_mutex_lock(&ph->f_m[ph->rf]);
	ft_print_message(ph, ph->nb, FORK, 0);
	ft_print_message(ph, ph->nb, EAT, 0);
	usleep(ph->to_eat * 1000);
	if (ph->num_eat != -1)
		ft_check_fed_optional(ph, ph->num_phs, 1);
	check_time(ph, 1);
	pthread_mutex_unlock(&ph->f_m[ph->lf]);
	pthread_mutex_unlock(&ph->f_m[ph->rf]);
}

void	ft_ts_first_queue(t_philo *ph)
{
	if (ph->nb % 2 != 0)
	{
		ft_print_message(ph, ph->nb, THINK, 0);
		usleep(ph->to_eat * 1000);
	}
	if (ph->nb == ph->num_phs - 1 && ph->nb % 2 == 0)
	{
		ft_print_message(ph, ph->nb, SLEEP, 0);
		if ((ph->to_sleep - ph->to_eat) > 0)
			usleep(ph->to_sleep * 1000);
		else
			usleep(ph->to_eat * 1000);
	}
}

void	ft_ts_second_queue(t_philo *ph)
{
	if (ph->nb % 2 == 0)
	{
		if (ph->nb != ph->num_phs - 1)
		{
			ft_print_message(ph, ph->nb, SLEEP, 0);
			if ((ph->to_sleep - ph->to_eat) > 0)
				usleep(ph->to_sleep * 1000);
			else
				usleep(ph->to_eat * 1000);
		}
		if (ph->nb == ph->num_phs - 1)
		{
			ft_print_message(ph, ph->nb, THINK, 0);
			usleep(ph->to_eat * 1000);
		}
	}
}

void	ft_for_odd_number(t_philo *ph)
{
	if (ph->nb % 2 != 0 && ph->nb != ph->num_phs - 1)
	{
		ft_print_message(ph, ph->nb, SLEEP, 0);
		if ((ph->to_sleep - ph->to_eat) > 0)
			usleep(ph->to_sleep * 1000);
		else
			usleep(ph->to_eat * 1000);
	}
	if (ph->nb == ph->num_phs - 1)
		ft_mute_forks_odd(ph);
	else if ((ph->nb != ph->num_phs - 1) && ph->nb % 2 == 0)
	{
		ft_print_message(ph, ph->nb, THINK, 0);
		usleep(ph->to_eat * 1000);
	}
}
