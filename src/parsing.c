/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:31:50 by ipetrov           #+#    #+#             */
/*   Updated: 2025/04/15 13:09:25 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
 * Input parsing
 *
 * - ??num of philos should be not more then 200
 * - ??time must be bigger then 60 ms
 *
 * - num of arguments should be 5 or 6
 * - num of philos can't be decimal
 * - num of meals can't be decimal
 * - not more then INT_MAX
 * - not negative
 * - args have to be only numeric
 *  number_of_philosophers time_to_die time_to_eat time_to_sleep
 *  [number_of_times_each_philosopher_must_eat]
 * ./philo    5    800  200   200     7
 * 		   philos  die  eat  sleep  meals
*/
int	parse_input(t_ctx *ctx, int ac, char **av)
{
	int	nbr;

	if (ac < 5 || ac > 6) // error wrong number of arguments
		return (puterr("wrong number of arguments"));
	if (ft_atoi(&nbr, av[1]) != SUCCESS)
		return (ERROR);
	ctx->nbr_philos = nbr;
	if (ft_atoi(&nbr, av[2]) != SUCCESS)
		return (ERROR);
	ctx->time_to_die = nbr;
	if (ft_atoi(&nbr, av[3]) != SUCCESS)
		return (ERROR);
	ctx->time_to_eat = nbr;
	if (ft_atoi(&nbr, av[4]) != SUCCESS)
		return (ERROR);
	ctx->time_to_sleep = nbr;
	if (ac == 6)
	{
		if (ft_atoi(&nbr, av[5]) != SUCCESS)
			return (ERROR);
	}
	else
		nbr = -1;
	ctx->nbr_meals = nbr;
	return (SUCCESS);
}
