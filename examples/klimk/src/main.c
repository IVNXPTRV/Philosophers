/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:39:22 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/23 14:39:31 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	exit_with_error_message(char *err_msg)
{
	printf("Error: %s", err_msg);
	exit(EXIT_FAILURE);
}

long long	get_timestamp(void)
{
	struct timeval	ct;

	gettimeofday(&ct, NULL);
	return ((ct.tv_sec * MS_PER_SEC) + (ct.tv_usec / US_PER_MS));
}

int	main(int argc, char **argv)
{
	t_sim			*sim;
	t_sim_params	params;

	params = parse_params((argc - 1), (argv + 1));
	sim = (t_sim *)malloc(sizeof(t_sim));
	if (!sim)
		exit_with_error_message(UNKNOWN_ERR);
	memset(sim, 0, sizeof(t_sim));
	if (init_sim(&sim, params) == ERROR)
	{
		handle_cleanup(&sim);
		exit_with_error_message(UNKNOWN_ERR);
	}
	run_sim(&sim);
	if (handle_cleanup(&sim) == ERROR)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
