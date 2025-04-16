/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:49:44 by ipetrov           #+#    #+#             */
/*   Updated: 2025/04/16 02:42:19 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
#define HEADER_H

#include <sys/time.h> // gettimeofday()
#include <pthread.h> // main ptrhead funcs
#include <stdbool.h> // bool datatype
#include <stdlib.h>  // for exit and EXIT_SUCCESS
#include <unistd.h> // write()
#include <stdint.h> // int64_t, INT32_MAX etc
#include <stdio.h> // printf

#define ERROR -1
#define SUCCESS 1

typedef struct s_ctx t_ctx;

enum e_atoi_codes
{
	NEGATIVE = 2,
	NONNUM,
	OVERFLOW32,
};

typedef struct s_fork
{
	int	id;
	pthread_mutex_t	lock;
} t_fork;

typedef long int t_time;

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
	long	nbr_philos;
	t_time	time_to_die;		// in milliseconds
	t_time	time_to_eat;		// in milliseconds
	t_time	time_to_sleep;		// in milliseconds
	long	nbr_meals;			// -1 if not provided
	t_time	start_time;			// in milliseconds
	t_philo	*philo; 			// array of philos
} t_ctx;


/*
 * UTILS
*/
size_t	ft_strlen(const char *str);
int	ft_atoi(int64_t *nbr, char *str);

int	puterr(char *msg);
int	parse_input(t_ctx *ctx, int ac, char **av);

#endif