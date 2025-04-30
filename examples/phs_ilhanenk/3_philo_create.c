/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_philo_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhanenk <ikhanenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:42:08 by ikhanenk          #+#    #+#             */
/*   Updated: 2025/04/22 21:02:54 by ikhanenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_create_arr(t_philo	**ph, t_params *params)
{
	int	*meals_num;
	int	i;

	if (params->num_eat != -1)
	{
		meals_num = malloc(sizeof(int) * params->num_phs);
		if (!meals_num)
			return ;
		i = -1;
		while (++i < params->num_phs)
			meals_num[i] = 0;
	}
	else
		meals_num = NULL;
	i = -1;
	while (++i < params->num_phs)
		(*ph + i)->meals_num = meals_num;
}

t_philo	*ft_create_phs(t_params *params)
{
	int		i;
	t_philo	*ph;
	long	start;

	ph = malloc(sizeof(t_philo) * (params->num_phs));
	if (!ph)
		return (NULL);
	start = ft_get_time();
	i = -1;
	while (++i < params->num_phs)
	{
		ph[i].nb = i;
		ph[i].num_phs = params->num_phs;
		ph[i].to_die = params->to_die;
		ph[i].to_eat = params->to_eat;
		ph[i].to_sleep = params->to_sleep;
		ph[i].num_eat = params->num_eat;
		ph[i].f_m = params->f_m;
		ph[i].last_eating = start;
		ph[i].start = start;
		ph[i].params = params;
		pthread_mutex_init(&(ph[i].th_time_lock), NULL);
	}
	ft_create_arr(&ph, params);
	return (ph);
}

void	ft_init_mutex(t_params *params)
{
	int	i;

	pthread_mutex_init(&params->fed_lock, NULL);
	pthread_mutex_init(&params->time_lock, NULL);
	pthread_mutex_init(&params->print_lock, NULL);
	params->f_m = malloc(sizeof(pthread_mutex_t) * params->num_phs);
	if (!params->f_m)
		return ;
	i = 0;
	while (i < params->num_phs)
	{
		pthread_mutex_init(&((params->f_m)[i]), NULL);
		i++;
	}
}

void	ft_create_phs_forks(t_philo **ph, t_params *params)
{
	ft_init_mutex(params);
	*ph = ft_create_phs(params);
	if (!*ph)
		return ;
}
