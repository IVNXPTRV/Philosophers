/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:49:44 by ipetrov           #+#    #+#             */
/*   Updated: 2025/04/24 13:15:16 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
#define HEADER_H

#include <sys/time.h> // gettimeofday()
#include <pthread.h> // main ptrhead funcs
#include <stdbool.h> // bool datatype
#include <stdlib.h>  // for exit and EXIT_OK
#include <unistd.h> // write()
#include <stdint.h> // t_int, INT32_MAX etc
#include <stdio.h> // printf()
#include <string.h> // memset()
#include <errno.h> // EINVAL and otehr codes

#define ER -1
#define DEBUG true
#define OK 1
#define WAIT 1
#define RUN 0
#define PRNME "philo: "
#define ERPTR "\xFF"
#define OKPTR "\x01"
#define MSG "%012ld %03ld %s"

typedef struct s_ctx t_ctx;
typedef pthread_mutex_t t_mtx;
typedef int64_t t_time; // time in microseconds
typedef int64_t t_int;
typedef pthread_t t_tid;

enum e_atoi_codes
{
	NEGATIVE = 2,
	NONNUM,
	OVERFLOW32,
};

typedef enum e_msg
{
	FORK_1,
	FORK_2,
	EAT,
	SLEEP,
	THINK,
	DIED
} t_msg;

typedef struct s_fork
{
	t_int	id;
	t_mtx	lock;
} t_fork;



typedef struct s_philo
{
	t_mtx			lock;				// protect internals of t_philo
	t_int			id;					// number of philo starting from 1
	t_tid			tid; 				// thread id internal for pthread
	t_int			status;				// status of philo
	t_ctx 			*ctx;				// ptr to context of whole simulation
	t_int 			meals_eaten;		// -1 if not provided, otherwise number of meals eaten
	t_fork			*first_fork;		// right fork
	t_fork			*second_fork;		// left fork
	t_time			last_meal_time;		// last meal start time in microseconds
} t_philo;

/*
 * context
*/
typedef struct s_ctx
{
	t_mtx			lock;				// protect internals of t_ctx and start lock for threads
	t_int			status;				// coordinate whole program to start or to end 2 - someone died, 1 - wait, 0 - run, -1 - ER
	t_int			num_philos;			// number of philos
	t_time			time_to_die;		// in microseconds
	t_time			time_to_eat;		// in microseconds
	t_time			time_to_sleep;		// in microseconds
	t_int			philos_full;		// -1 if meals not provided, temporary hold meals_to_eat before t_philo initialized
	t_time			start_time;			// simulation starting point in microseconds
	t_philo			*philos; 			// array of philos
	t_fork			*forks; 			// array of forks
} t_ctx;


/*
 * UTILS
*/
size_t	ft_strlen(const char *str);
int		ft_atoi(t_int *num, char *str);
void	*ft_calloc(size_t num, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memcpy(void *dest, const void *src, size_t n);

/**
 * PRINT
 */
int		puterr(char *msg);
int		put_msg(t_philo *philo, t_msg msg);


/**
 * TIME
 */
int	get_time(t_time *timestamp, t_time start_time);
int	psleep(t_time time);

/**
 * PARSING
 */
int		parse_input(t_ctx *ctx, int ac, char **av);

/**
 * SIMULATING
 *
 */
int		run_simulation(t_ctx *ctx);
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
int	set_val(t_mtx *lock, void *var, void *src);
int	get_val(t_mtx *lock, void *var, void *dst);
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