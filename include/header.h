/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:49:44 by ipetrov           #+#    #+#             */
/*   Updated: 2025/04/24 02:23:04 by ipetrov          ###   ########.fr       */
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
#define DIED 2
#define WAIT 1
#define RUN 0
#define ERRNAME "philo: "
#define ERRPTR "\xFF"
#define SUCPTR "\x01"

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
	int64_t	id;
	t_mtx	lock;
} t_fork;

typedef int64_t t_time;

typedef struct s_philo
{
	int64_t			id;
	int64_t 		meals_to_eat;		// -1 if not provided, otherwise N to eat
	t_ctx 			*ctx;
	pthread_t		tid; 				// thread id
	t_fork			*first_fork;		// left
	t_fork			*second_fork;		// right
	t_time			last_meal_time;
	t_time			time;
} t_philo;

/*
 * context
*/
typedef struct s_ctx
{
	int64_t			status;				// coordinate whole program to start or to end 2 - someone died, 1 - wait, 0 - run, -1 - error
	t_mtx			lock;				// protect internals of t_ctx
	int64_t			nbr_philos;			// number of philos
	t_time			time_to_die;		// in milliseconds
	t_time			time_to_eat;		// in milliseconds
	t_time			time_to_sleep;		// in milliseconds
	int64_t			philos_full;		// -1 if meals not provided, temporary hold meals_to_eat before t_philo initialized
	t_time			start_time;			// in milliseconds
	t_philo			*philos; 			// array of philos
	t_fork			*forks; 			// array of forks
} t_ctx;


/*
 * UTILS
*/
size_t	ft_strlen(const char *str);
int		ft_atoi(int64_t *nbr, char *str);
char	*ft_itoa(int64_t n);
void	*ft_calloc(size_t num, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memcpy(void *dest, const void *src, size_t n);

/**
 * PRINT
 */
int		puterr(char *msg);
int	put_philo_msg(t_philo *philo, t_time time, char *msg);


/**
 * TIME
 */
int	get_time(t_time *timestamp, t_time start_time);
int	philo_wait(t_time time);

/**
 * PARSING
 */
int		parse_input(t_ctx *ctx, int ac, char **av);

/**
 * SIMULATING
 *
 */
int run_simulation(t_ctx *ctx);
void	*philo_routine(void *ptr);

/**
 * INITIALIZING
 *
 */
int	init_data(t_ctx *ctx);

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
int clean(t_ctx *ctx);

#endif