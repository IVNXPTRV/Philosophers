/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliashko <sliashko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:26:57 by sliashko          #+#    #+#             */
/*   Updated: 2024/02/07 17:55:22 by sliashko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	unsigned int	num;
	int				i;
	int				np;

	np = 1;
	i = 0;
	num = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == '\n' || str[i] == '\v')
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			np = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(np * num));
}

void	free_forks(pthread_mutex_t **forks, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(forks[i]);
		free(forks[i]);
		i++;
	}
	free(forks);
}

void	free_philos(t_philo_data **philos)
{
	int	i;

	i = 0;
	while (i < philos[0]->n)
	{
		free(philos[i]);
		i++;
	}
	free(philos);
}

void	free_muts(t_philo_data *philo)
{
	pthread_mutex_destroy(philo->muts->print_mut);
	pthread_mutex_destroy(philo->muts->exit_mut);
	free(philo->muts->print_mut);
	free(philo->muts->exit_mut);
	free(philo->muts);
}
