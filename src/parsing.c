/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:31:50 by ipetrov           #+#    #+#             */
/*   Updated: 2025/04/16 12:04:23 by ipetrov          ###   ########.fr       */
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
 * - num of meals can't be zero
 *
 *  number_of_philosophers time_to_die time_to_eat time_to_sleep
 *  [number_of_times_each_philosopher_must_eat]
 * ./philo    5    800  200   200     7
 * 		   philos  die  eat  sleep  meals
*/
int	parse_input(t_ctx *ctx, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (puterr(ERRNAME"wrong number of arguments\n"));
	if (ft_atoi(&ctx->nbr_philos, av[1]) != SUCCESS)
		return (ERROR);
	if (ctx->nbr_philos == 0)
		return (puterr(ERRNAME"number of philos has to be greater then 0\n"));
	if (ft_atoi(&ctx->time_to_die, av[2]) != SUCCESS)
		return (ERROR);
	if (ft_atoi(&ctx->time_to_eat, av[3]) != SUCCESS)
		return (ERROR);
	if (ft_atoi(&ctx->time_to_sleep, av[4]) != SUCCESS)
		return (ERROR);
	if (ctx->time_to_die == 0 || ctx->time_to_eat == 0 || ctx->time_to_sleep == 0)
		return (puterr(ERRNAME"time has to be greater then 0\n"));
	ctx->philos_full = -1;
	if (av[5] && ft_atoi(&ctx->philos_full , av[5]) != SUCCESS)
		return (ERROR);
	if (ctx->philos_full == 0)
		return (puterr(ERRNAME"number of meals can't be 0\n"));
	return (SUCCESS);
}
