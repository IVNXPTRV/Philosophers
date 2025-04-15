/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 06:39:58 by ipetrov           #+#    #+#             */
/*   Updated: 2025/04/15 08:39:06 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <errno.h>
#include <stdlib.h>  // for exit and EXIT_SUCCESS

#define ERROR -1

typedef struct s_fork
{
	int	id;
	pthread_mutex_t	lock;
} t_fork;

typedef long long t_time;

typedef struct s_philo
{
	int			id;
	bool 		full;
	bool 		dead;
	t_ctx 		*ctx;
	pthread_t	ptid; 				// pthread thread id
	int 		meals_eaten;
	t_fork		*first_fork;
	t_fork		*second_fork;
	t_time		last_meal_time;
} t_philo;

/*
 * context
*/
typedef struct s_ctx
{
	int		nbr_philos;
	t_time	time_to_die;		// in milliseconds
	t_time	time_to_eat;		// in milliseconds
	t_time	time_to_sleep;		// in milliseconds
	int		nbr_meals;			// -1 if not provided
	t_time	start_time;			// in milliseconds
	t_philo	*philo; 			// array of philos
} t_ctx;

/*
 * Cleans everything
*/
void	clean(t_ctx *ctx)
{
	// TODO: implement otehr cleaning here;
}
/*
 * error exit
 * prints error message
 * it doesnt clean anything
 * exits the program
*/
void	ft_perror(char *msg)
{
	printf("philo: %s\n", msg); // dont need to check for error we already almost exited
}

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
	{
		ft_perror(errno);
		return (ERROR);
	}
	return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3) - start_time);
}

/*
 * Input parsing
 * - num or arguments should be 5 or 6
 * - num or philos should be not more then 200
 * - num of philos can't be decimal
 * - num of meals can't be decimal
 * - int max??
 * - args have to be only numeric
 * -
*/
int	parse_input(t_ctx *ctx, int ac, char **av)
{
	if (ac != 5 || ac != 6)
	{
		ft_perror("wrong number of arguments"); // error wrong number of arguments
		return (ERROR);
	}


}
/*
 * Initializing main structures
 *
*/
void	init_data(t_ctx *ctx)
{

}


/*
 * ./philo 5 800 200 200 7 -- no one dies, sim stops when each philo has eaten 7 meals
*/
int	main(int ac, char **av)
{
	t_ctx	ctx;

	if (parse_input(&ctx, ac, av) == ERROR)
	(
		clean(&ctx);
		return (EXIT_FAILURE);
	)
	init_data(&ctx);
	run_simulation(&ctx);
	clean(&ctx);
	return (EXIT_SUCCESS);
}