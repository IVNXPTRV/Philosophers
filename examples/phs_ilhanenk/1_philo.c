/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhanenk <ikhanenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 22:05:32 by ikhanenk          #+#    #+#             */
/*   Updated: 2025/04/07 22:05:32 by ikhanenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_check_death(void *philo)
{
	t_philo	*ph;
	int		i;
	int		pn;

	ph = (t_philo *)philo;
	pn = ph->params->num_phs;
	while (1)
	{
		i = 0;
		while (i < ph->params->num_phs)
		{
			if ((ft_get_time() - check_time((ph + i), 0) >= ph->to_die) \
					&& (ft_print_message((ph + i), (ph + i)->nb, DIE, 1) == 1))
				return (NULL);
			else if (ph->params->num_eat != -1 && \
					(ft_check_fed_optional(ph + i, pn, 0) == 1) \
					&& (ft_print_message((ph + i), (ph + i)->nb, FED, 1) == 1))
				return (NULL);
			i++;
		}
	}
	return (NULL);
}

void	*ft_dinner(void *philo)
{
	t_philo		*ph;

	ph = (t_philo *)philo;
	while (1)
	{
		ft_ph_eat(ph);
		if (ft_print_message(ph, ph->nb, NOT, 0) == 1)
			return (NULL);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo			*ph;
	t_params		params;

	if (argc < 5 || argc > 6)
		return (write(2, "Wrong number of arguments\n", 26));
	if (ft_check_and_init_args(argc, argv, &params) != 0)
		return (EXIT_FAILURE);
	params.death_or_fed = 0;
	ft_create_phs_forks(&ph, &params);
	ft_start_threads(ph);
	ft_join_threads(ph);
	ft_cleaner(ph);
	return (0);
}
