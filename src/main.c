/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 06:39:58 by ipetrov           #+#    #+#             */
/*   Updated: 2025/04/16 06:12:30 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
 * ./philo 5 800 200 200 7 -- no one dies, sim stops when each philo has eaten 7 meals
 *
 * ./philo    5    800  200   200     7
 * 		   philos  die  eat  sleep  meals
*/
int	main(int ac, char **av)
{
	t_ctx	ctx;

	memset(&ctx, 0, sizeof(t_ctx));
	if (parse_input(&ctx, ac, av) != SUCCESS)
		return (EXIT_FAILURE);
	init_data(&ctx);
	// run_simulation(&ctx);
	// clean(&ctx);
	return (EXIT_SUCCESS);
}