/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:49:44 by ipetrov           #+#    #+#             */
/*   Updated: 2025/04/16 09:55:03 by ipetrov          ###   ########.fr       */
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
#include <stdio.h> // printf()
#include <string.h> // memset()
#include <errno.h> // EINVAL and otehr codes

#define ERROR -1
#define SUCCESS 1
#define ERRNAME "philo: "

typedef struct s_ctx t_ctx;
typedef pthread_mutex_t t_mtx;

enum e_atoi_codes
{
	NEGATIVE = 2,
	NONNUM,
	OVERFLOW32,
};

typedef struct s_fork
{
	int32_t	id;
	t_mtx	lock;
} t_fork;

typedef int32_t t_time;

typedef struct s_philo
{
	int32_t			id;
	t_mtx			lock;				// protect internals of t_philo
	bool 			full;				// philo lock mutex and set this bool to true when eaten enough
	int32_t 		meals_eaten;
	t_ctx 			*ctx;
	pthread_t		tid; 				// thread id
	t_fork			*first_fork;		// left
	t_fork			*second_fork;		// right
	t_time			last_meal_time;
} t_philo;

/*
 * context
*/
typedef struct s_ctx
{
	int32_t			status;				// coordinate whole program to start or to end 1 - wait, 0 - run, -1 - error
	t_mtx			lock;				// protect internals of t_ctx
	int32_t			nbr_philos;			// number of philos
	t_time			time_to_die;		// in milliseconds
	t_time			time_to_eat;		// in milliseconds
	t_time			time_to_sleep;		// in milliseconds
	int32_t			nbr_meals;			// -1 if not provided
	t_time			start_time;			// in milliseconds
	t_philo			*philos; 			// array of philos
	t_fork			*forks; 			// array of forks
} t_ctx;


/*
 * UTILS
*/
size_t	ft_strlen(const char *str);
int		ft_atoi(int32_t *nbr, char *str);
char	*ft_itoa(int32_t n);
void	*ft_calloc(size_t num, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memcpy(void *dest, const void *src, size_t n);

/**
 * PRINT
 */
int		puterr(char *msg);

/**
 * TIME
 */
int	get_time(t_time *timestamp, t_time start_time);

/**
 * PARSING
 */
int		parse_input(t_ctx *ctx, int ac, char **av);

/**
 * SIMULATING
 *
 */
void	philo_routine(void *ptr);

/**
 * MUTEX
 *
 */
int	set_val(t_mtx *lock, void *var, void *src, size_t size_of);
int	get_val(t_mtx *lock, void *var, void *dst, size_t size_of);
int	mtx_init(t_mtx *mtx);
int	mtx_destroy(t_mtx *mtx);
int	mtx_lock(t_mtx *lock);
int	mtx_unlock(t_mtx *lock);

/**
 * THREAD
 *
 */
int th_create(pthread_t *tid, void *func(void *), void *arg);
int th_join(pthread_t *tid);

/**
 * CLEANING
 *
 */
int clean_forks(t_fork **forks);
int clean_philos(t_philo **philos);
int	clean_ctx(t_ctx **ctx);

#endif