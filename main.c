/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 06:39:58 by ipetrov           #+#    #+#             */
/*   Updated: 2025/04/15 07:07:33 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>


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
	bool 		*end; 				//end simulation if true, someone died
	t_ctx 		*ctx;
	pthread_t	ptid; 				//pthread thread id
	int 		meals_eaten;
	t_fork		*first_fork;
	t_fork		*second_fork;
	t_time		last_meal_time;
} t_philo;

typedef struct s_ctx
{
	bool	*end;				//end simulation if true, someone died
	t_philo	*philo; 			//array of philos
	int		nbr_philo;
	int		nbr_meals;
	t_time	time_to_die;
	t_time	time_to_eat;
	t_time	time_to_sleep;
} t_ctx;

//returns time in ms since first call of this function
t_time	get_time(void)
{
	static t_time start_time;
	struct timeval tv;

	gettimeofday(&tv, NULL);
	if (!start_time)
		start_time = (tv.tv_sec * 1e3) + (tv.tv_usec / 1e3);
	return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3) - start_time);
}

int	main()
{
	printf("time: %lld\n", get_time());
	sleep(2);
	printf("time: %lld\n", get_time());

}