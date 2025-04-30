/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhanenk <ikhanenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:28:29 by ikhanenk          #+#    #+#             */
/*   Updated: 2025/04/21 20:28:29 by ikhanenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <ctype.h>

#define NOT     -1
#define EAT 	0
#define FORK 	1
#define THINK 	2
#define SLEEP 	3
#define DIE 	4
#define FED     5
#define BLUE "\033[38;5;68m"
#define SKY_BLUE "\033[38;5;31m"
#define RED "\033[38;5;168m"
#define DFT "\033[0m"
#define WHITE "\033[38;5;15m"

typedef struct s_params
{
	int				num_phs;
	int				to_die;
	int				to_eat;
	int				to_sleep;
	int				num_eat;
	int				death_or_fed;
	pthread_t		check_phs_died;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	fed_lock;
	pthread_mutex_t	fed_lock_2;
	pthread_mutex_t	time_lock;
	pthread_mutex_t	*f_m;
}	t_params;

typedef struct s_philo
{
	t_params		*params;
	int				nb;
	int				num_phs;
	int				to_die;
	int				to_eat;
	int				to_sleep;
	int				num_eat;
	int				*meals_num;
	pthread_mutex_t	th_time_lock;
	long			last_eating;
	long			start;
	int				rf;
	int				lf;
	pthread_t		thread;
	pthread_mutex_t	*f_m;
}	t_philo;

// philo.c
void	*ft_dinner(void *philo);
long	check_time(t_philo *ph, int n);
void	*ft_check_death(void *philo);

// philo_init.c
int		ft_check_and_init_args(int argc, char **argv, t_params *params);
int		ft_check_digit(char *str);

// philo_create.c
void	ft_create_phs_forks(t_philo **ph, t_params *params);
t_philo	*ft_create_phs(t_params *params);
void	ft_create_arr(t_philo	**ph, t_params *params);
void	ft_init_mutex(t_params *params);

// philo_utils.c
void	ft_find_forks(t_philo *ph);
void	ft_ph_eat(t_philo *ph);
int		ft_check_fed_optional(t_philo *ph, int num_phs, int add);
// void	*lock(t_philo *ph);

// philo_utils_2.c
long	ft_get_time(void);
int		ft_print_message(t_philo *ph, int nb, int status, int change);
void	ft_mute_forks_odd(t_philo *ph);
void	ft_mute_forks_even(t_philo *ph);
void	ft_start_threads(t_philo *ph);
void	ft_join_threads(t_philo *ph);
void	ft_cleaner(t_philo *ph);

// lock.c
void	ft_ts_first_queue(t_philo *ph);
void	ft_ts_second_queue(t_philo *ph);
void	ft_for_odd_number(t_philo *ph);
int		check_death_or_fed(t_philo *ph, int change);

// philo_utils_libft.h
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *s);
