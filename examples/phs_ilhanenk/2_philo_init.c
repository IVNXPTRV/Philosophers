/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_philo_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhanenk <ikhanenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:52:43 by ikhanenk          #+#    #+#             */
/*   Updated: 2025/04/30 17:57:59 by ikhanenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (isdigit(str[i]))
			i++;
		else
			return (1);
	}
	return (0);
}

int	ft_check_and_init_args(int argc, char **argv, t_params *params)
{
	int	i;
	int	n;

	i = 0;
	while (++i < argc)
	{
		n = ft_atoi(argv[i]);
		if (i == 1 && (n < 1 || n > 500))
			return (write(2, "Number of phs should be > 0 and < 200\n", 38));
		if (i != 1 && i != 5)
		{
			if (n < 60 || n > 1000000 || ft_check_digit(argv[i]) != 0)
				return (write(2, "Write num > 60 and < 1000000 ms\n", 41));
		}
	}
	params->num_phs = ft_atoi(argv[1]);
	params->to_die = ft_atoi(argv[2]);
	params->to_eat = ft_atoi(argv[3]);
	params->to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		params->num_eat = ft_atoi(argv[5]);
	else
		params->num_eat = -1;
	return (0);
}
