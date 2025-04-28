/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 06:39:58 by ipetrov           #+#    #+#             */
/*   Updated: 2025/04/28 09:15:06 by ipetrov          ###   ########.fr       */
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
	if (parse_input(&ctx, ac, av) != OK)
		return (EXIT_FAILURE);
	if (init_data(&ctx) != OK)
		return (EXIT_FAILURE);
	run_simulation(&ctx);
	clean(&ctx);
	return (EXIT_SUCCESS);
}

// // tester for philo_wait
// int	main()
// {
// 	t_time start;
// 	t_time end;

// 	get_time(&start, 0);
// 	philo_wait(10000);
// 	get_time(&end, 0);
// 	printf("real wait: %ld\n", end - start);
// 	return (EXIT_SUCCESS);
// }