/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 06:39:58 by ipetrov           #+#    #+#             */
/*   Updated: 2025/04/16 02:05:05 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"


// /*
//  * Cleans everything
// */
// void	clean(t_ctx *ctx)
// {
// 	// TODO: implement other cleaning here;
// }


// /**
//  * @brief
//  * timestamp_in_ms X has taken a fork
//  * timestamp_in_ms X is eating
//  * timestamp_in_ms X is sleeping
//  * timestamp_in_ms X is thinking
//  * timestamp_in_ms X died
//  * @param msg
//  */
// int	putmsg(t_philo philo, char *msg)
// {

// 	// convert time to string
// 	// convert id to string
// 	write(STDOUT_FILENO, "philo: ", 7);
// 	write(STDOUT_FILENO, msg, ft_strlen(msg));
// 	write(STDERR_FILENO, "\n", 1);
// 	// dont need to check for error we already almost exited
// }

//
/*
 *
*/

/**
 * @brief Get time in ms since the begining of the simulation
 *
 * @param start_time timestamp in ms of the begining of the simulation since epoch
 * @return t_time in ms since the begining of the simulation
 */
t_time	get_time(t_time start_time)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == ERROR)
		return (puterr("gettimeofday() error"));
	return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3) - start_time);
}


// /*
//  * Initializing main structures
//  *
// */
// void	init_data(t_ctx *ctx)
// {

// }


/*
 * ./philo 5 800 200 200 7 -- no one dies, sim stops when each philo has eaten 7 meals
 *
 * ./philo    5    800  200   200     7
 * 		   philos  die  eat  sleep  meals
*/
int	main(int ac, char **av)
{
	t_ctx	ctx;

	if (parse_input(&ctx, ac, av) != SUCCESS)
		return (EXIT_FAILURE);
	// init_data(&ctx);
	// run_simulation(&ctx);
	// clean(&ctx);
	return (EXIT_SUCCESS);
}