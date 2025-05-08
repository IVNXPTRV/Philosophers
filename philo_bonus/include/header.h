/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:49:44 by ipetrov           #+#    #+#             */
/*   Updated: 2025/05/08 04:27:46 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <errno.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h> // sem_open
# include <fcntl.h>           /* For O_* constants */

# define DEBUG false
# define UNDEFINED -1
# define TRUE true
# define FALSE false
# define OK 1
# define ER -1
# define FAIL 0
# define EPOCH 0
# define WAIT 1
# define RUN 0
# define PRNME "philo: "
# define ERPTR "\xFF"
# define OKPTR "\x01"
# define MSG "%lld %lld %s"
# define TIMEOUT 200
# define RED "\033[31m"
# define RESET "\033[0m\n"

typedef long long int	t_int;
typedef double			t_dec;
typedef t_int			t_sts;
typedef t_int			t_bool;
typedef t_int			t_time;

typedef struct s_ctx	t_ctx;
typedef pthread_mutex_t	t_mtx;
typedef pthread_t		t_tid;

enum					e_atoi_codes
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
}						t_msg;

typedef enum e_time_type
{
	US,
	MS
}						t_time_type;

typedef struct s_fork
{
	t_int				id;
	t_mtx				lock;
	t_bool				state;
}						t_fork;

typedef struct s_philo
{
	t_int			id;					// number of philo starting from 1
	pid_t			pid; 				// process id
	// VAR
	sem_t			*lock;				// serialization lock, binary semaphore
	t_int 			meals_eaten;		// -1 if not provided, otherwise number of meals eaten
	sem_t			*forks;				// total number of forks represented as one semaphore with value of total num of forks
	t_time			last_meal_time;		// last meal start time in milliseconds
	// CONST
	t_int			num_philos;			// number of philos
	t_time			time_to_die;		// in milliseconds, read-only
	t_time			time_to_eat;		// in milliseconds, read-only
	t_time			time_to_sleep;		// in milliseconds, read-only
	t_time			time_to_think;		// in milliseconds, read-only
	t_int			meals_to_eat;		// num of meals to eat -1 if UNDEFINED
	t_time			start_time;			// simulation starting point in milliseconds
} t_philo;

/*
 * context
*/
typedef struct s_ctx
{
	sem_t			*lock;				// serialization lock, binary semaphore
	// ** CONST **
	t_int			num_philos;			// number of philos
	t_int			meals_to_eat;		// num of meals to eat -1 if UNDEFINED
	t_time			time_to_die;		// in mlliseconds, read-only
	t_time			time_to_eat;		// in mlliseconds, read-only
	t_time			time_to_sleep;		// in mlliseconds, read-only
	t_time			time_to_think;		// in mlliseconds, read-only
	t_time			start_time;			// simulation starting point in mlliseconds
	// ** TO CLEAN **
	t_philo			*philos; 			// array of philos PID
	sem_t			*forks; 			// array of forks
} t_ctx;						t_ctx;

/*
 * UTILS
 */
size_t					ft_strlen(const char *str);
t_sts					ft_atoi(t_int *num, char *str);
void					*ft_calloc(size_t num, size_t size);
char					*ft_strjoin(char const *s1, char const *s2);
void					*ft_memcpy(void *dest, const void *src, size_t n);

/**
 * PRINT
 */
t_sts					puterr(char *msg);
t_sts					putmsg(t_philo *philo, t_time now, t_msg msg);

/**
 * STATUS
 */
t_sts					is_dead(t_philo *philo, t_time now);
t_sts					is_end(t_ctx *ctx);

/**
 * TIME
 */
t_sts					get_time(t_time_type type, t_time *dst,
							t_time start_time);
t_sts					smart_sleep(t_time waittime, t_ctx *ctx);

/**
 * PARSING
 */
t_sts					parse_input(t_ctx *ctx, t_int ac, char **av);

/**
 * SIMULATING
 *
 */
t_sts					run_simulation(t_ctx *ctx);
void					*philo_routine(void *ptr);
t_sts					check_in_meal(t_philo *philo, t_time now);
t_sts					is_all_full(t_philo *philo);
t_sts					take_forks(t_philo *philo, t_time now);
t_sts					release_forks(t_philo *philo);
t_sts					philo_eat(t_philo *philo);

/**
 * INITIALIZING
 *
 */
t_sts					init_data(t_ctx *ctx);

/**
 * MONITOR
 *
 */
t_sts					death_monitor(t_ctx *ctx);

/**
 * MUTEX
 *
 */
t_sts					mtx_init(t_mtx *mtx);
t_sts					mtx_destroy(t_mtx *mtx);
t_sts					mtx_lock(t_mtx *lock);
t_sts					mtx_unlock(t_mtx *lock);

/**
 * THREAD
 *
 */
t_sts					th_create(pthread_t *tid, void *func(void *),
							void *arg);
t_sts					th_join(pthread_t *tid);

/**
 * CLEANING
 *
 */
t_int					clean_forks(t_ctx *ctx);
t_sts					clean_philos(t_philo **philos);
t_sts					clean_ctx(t_ctx **ctx);
t_sts					clean(t_ctx *ctx);

#endif