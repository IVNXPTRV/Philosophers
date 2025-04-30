/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:49:44 by ipetrov           #+#    #+#             */
/*   Updated: 2025/04/30 09:50:22 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
#define HEADER_H

#include <sys/time.h> // gettimeofday()
#include <pthread.h> // main ptrhead funcs
#include <stdbool.h> // bool datatype
#include <stdint.h> // t_int, INT32_MAX etc
#include <stdlib.h>  // for exit and EXIT_OK
#include <unistd.h> // write()
#include <stdio.h> // printf()
#include <string.h> // memset()
#include <errno.h> // EINVAL and otehr codes

#define DEBUG false
#define UNDEFINED -1
#define TRUE true
#define FALSE false
#define OK 1
#define ER -1
#define FAIL 0
#define EPOCH 0
#define WAIT 1
#define RUN 0
#define PRNME "philo: "
#define ERPTR "\xFF"
#define OKPTR "\x01"
#define MSG "%lld %lld %s" // "%12lld %3lld %s"
#define TIMEOUT 200 // 100ms timeout for sleeping or eating to check if simulation should be ended
#define RED     "\033[31m"
#define RESET   "\033[0m\n"
#define DBGMSG RED"here"RESET


typedef long long int t_int;
typedef double t_dec;
typedef t_int t_sts;
typedef t_int t_bool;
typedef t_int t_time;

typedef struct s_ctx t_ctx;
typedef pthread_mutex_t t_mtx;
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
	DIED,
} t_msg;

typedef enum e_time_type
{
	US, // microseconds
	MS  // milliseconds
} t_time_type;


typedef struct s_fork
{
	t_int	id;							// id of fork starting from 1
	t_mtx	lock;						// mutex to protect state
	t_bool	state;						// true if taken, false if avaliable
} t_fork;

typedef struct s_philo
{
	t_int			id;					// number of philo starting from 1
	t_tid			tid; 				// thread id internal for pthread
	t_int 			meals_eaten;		// -1 if not provided, otherwise number of meals eaten
	t_time			last_meal_time;		// last meal start time in mlliseconds
	t_fork			*fork_one;			// right fork
	t_fork			*fork_two;			// left fork
	t_ctx 			*ctx;				// ptr to context of whole simulation
} t_philo;

/*
 * context
*/
typedef struct s_ctx
{
	t_mtx			lock;				// protect internals of t_ctx and start lock for threads
	// ** VARS **
	t_bool			end;				// true if sim ended
	t_int			num_full_philos;	// number of full philos
	// ** CONST **
	t_int			num_philos;			// number of philos
	t_int			meals_to_eat;		// num of meals to eat -1 if UNDEFINED
	t_time			time_to_die;		// in mlliseconds, read-only
	t_time			time_to_eat;		// in mlliseconds, read-only
	t_time			time_to_sleep;		// in mlliseconds, read-only
	t_time			time_to_think;		// in mlliseconds, read-only
	t_time			start_time;			// simulation starting point in mlliseconds
	// ** TO CLEAN **
	t_philo			*philos; 			// array of philos
	t_fork			*forks; 			// array of forks
} t_ctx;

// t_int			philos_full;		dont nee cause if one not full just break // -1 if meals not provided, temporary hold meals_to_eat before t_philo initialized

/*
 * UTILS
*/
size_t	ft_strlen(const char *str);
t_sts	ft_atoi(t_int *num, char *str);
void	*ft_calloc(size_t num, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memcpy(void *dest, const void *src, size_t n);

/**
 * PRINT
 */
t_sts	puterr(char *msg);
t_sts	putmsg(t_philo *philo, t_time now, t_msg msg);

/**
 * STATUS
 */
t_sts is_dead(t_philo *philo, t_time now);
t_sts is_end(t_ctx *ctx);

/**
 * TIME
 */
t_sts	get_time(t_time_type type, t_time *dst, t_time start_time);
t_sts	smart_sleep(t_time waittime, t_ctx *ctx);
/**
 * PARSING
 */
t_sts	parse_input(t_ctx *ctx, t_int ac, char **av);

/**
 * SIMULATING
 *
 */
t_sts	run_simulation(t_ctx *ctx);
void	*philo_routine(void *ptr);
t_sts	check_in_meal(t_philo *philo, t_time now);
t_sts is_all_full(t_philo *philo);

/**
 * INITIALIZING
 *
 */
t_sts	init_data(t_ctx *ctx);

/**
 * MONITOR
 *
 */
t_sts	death_monitor(t_ctx *ctx);

/**
 * MUTEX
 *
 */
t_sts	set_val(t_mtx *lock, void *dst, void *src);
t_sts	get_val(t_mtx *lock, void *src, void *dst);
t_sts	mtx_init(t_mtx *mtx);
t_sts	mtx_destroy(t_mtx *mtx);
t_sts	mtx_lock(t_mtx *lock);
t_sts	mtx_unlock(t_mtx *lock);

/**
 * THREAD
 *
 */
t_sts th_create(pthread_t *tid, void *func(void *), void *arg);
t_sts th_join(pthread_t *tid);

/**
 * CLEANING
 *
 */
t_int	clean_forks(t_ctx *ctx);
t_sts	clean_philos(t_philo **philos);
t_sts	clean_ctx(t_ctx **ctx);
t_sts	clean(t_ctx *ctx);

#endif