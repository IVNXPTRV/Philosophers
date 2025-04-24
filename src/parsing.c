/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:31:50 by ipetrov           #+#    #+#             */
/*   Updated: 2025/04/24 13:03:12 by ipetrov          ###   ########.fr       */
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
		return (puterr(PRNME"wrong number of arguments\n"));
	if (ft_atoi(&ctx->num_philos, av[1]) != OK)
		return (ER);
	if (ctx->num_philos == 0)
		return (puterr(PRNME"number of philos has to be greater then 0\n"));
	if (ft_atoi(&ctx->time_to_die, av[2]) != OK)
		return (ER);
	if (ft_atoi(&ctx->time_to_eat, av[3]) != OK)
		return (ER);
	if (ft_atoi(&ctx->time_to_sleep, av[4]) != OK)
		return (ER);
	if (ctx->time_to_die == 0 || ctx->time_to_eat == 0 || ctx->time_to_sleep == 0)
		return (puterr(PRNME"time has to be greater then 0\n"));
	ctx->philos_full = -1;
	if (av[5] && ft_atoi(&ctx->philos_full, av[5]) != OK)
		return (ER);
	if (ctx->philos_full == 0)
		return (puterr(PRNME"number of meals can't be 0\n"));
	ctx->time_to_die *= 1e3; // convert input to microseconds
	ctx->time_to_eat *= 1e3; // convert input to microseconds
	ctx->time_to_sleep *= 1e3; // convert input to microseconds
	return (OK);
}
