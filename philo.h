/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 21:45:19 by edgar             #+#    #+#             */
/*   Updated: 2025/07/29 23:55:48 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>
#include <errno.h>

# define RED     "\033[0;31m"
# define RESET   "\033[0m"

typedef enum s_log_types
{
	EAT,
	TAKE_FORK,
	THINK,
	SLEEP,
	DEAD
}	t_log_types;

# define ARGS_COUNT_ERR 1
# define ARGS_EMPTY_ERR 2
# define ARGS_INV_NBR_ERR 3
# define ARGS_NEG_NULL_NBR_ERR 4
# define MEM_FAIL 5
# define THREADS_FINISH_FAIL 6
# define THREADS_CREATE_FAIL 7
# define MUTEX_INIT_FAIL 8

typedef struct	s_simulation_data
{
	int				nbr_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				sim_err;
	int				nbr_philo_has_eaten;
	int				sim_end;
	int				log_mutex_initialized;
	int				sim_end_mutex_initialized;
	int				monitor_thread_initialized;
	int				forks_initialized;
	long			start_time_ms;
	pthread_mutex_t	*forks;
	pthread_mutex_t log_mutex;
	pthread_mutex_t	sim_end_mutex;
	pthread_t		monitor_th;
} t_simulation_data;

typedef struct	s_philo
{
	int					id;
	int					times_eated;
	int					died;
	int					times_eated_mutex_initialized;
	int					dead_mutex_initialized;
	int					thread_initialized;
	long				last_time_eated;
	pthread_t			th;
	pthread_mutex_t		times_eated_mutex;
	pthread_mutex_t		dead_mutex;
	pthread_mutex_t		*fork1;
	pthread_mutex_t		*fork2;
	t_simulation_data	*sim;
} t_philo;


/* Utils */
long long	ft_atoll(char *nbr);
int			ft_strlen(char *str);
long		get_timestamp_ms(void);
/* Validator */
int			is_not_a_valid_sim(t_simulation_data *sim, int argc, char **argv);
/* Threads */
int			create_threads(t_simulation_data *sim, t_philo *philos);
/* Routine */
void 		*routine(void *arg);
/* Logger */
void		log_message(t_philo *philo, int log_type);
/* Mutexes */
int			init_mutexes(t_simulation_data *sim, t_philo *philos);
/* Cleaner */
int			clean_all(t_simulation_data *sim, t_philo *philos, int exit_status);

#endif 