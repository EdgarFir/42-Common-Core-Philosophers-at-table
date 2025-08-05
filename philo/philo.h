/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 21:45:19 by edgar             #+#    #+#             */
/*   Updated: 2025/08/04 22:39:09 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H
# define RED     "\033[0;31m"
# define RESET   "\033[0m"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <errno.h>

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
# define NBR_PHILOS_ERR 5
# define TIME_MIN_VALUE_ERROR 6
# define MEM_FAIL 7
# define THREADS_FINISH_FAIL 8
# define THREADS_CREATE_FAIL 9
# define MUTEX_INIT_FAIL 10

typedef struct s_sim_data
{
	int				nbr_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_times;
	int				sim_err;
	int				sim_end;
	int				log_mutex_initialized;
	int				sim_end_mutex_initialized;
	int				monitor_thread_initialized;
	int				forks_initialized;
	long			start_time_ms;
	pthread_mutex_t	*forks;
	pthread_mutex_t	log_mutex;
	pthread_mutex_t	sim_end_mutex;
	pthread_t		monitor_th;
}	t_sim_data;

typedef struct s_philo
{
	int					id;
	int					times_eated;
	int					died;
	int					times_eated_mutex_initialized;
	int					dead_mutex_initialized;
	int					last_time_eated_mutex_initialized;
	int					thread_initialized;
	long				last_time_eated;
	pthread_t			th;
	pthread_mutex_t		times_eated_mutex;
	pthread_mutex_t		dead_mutex;
	pthread_mutex_t		last_time_eated_mutex;
	pthread_mutex_t		*fork1;
	pthread_mutex_t		*fork2;
	t_sim_data			*sim;
}	t_philo;

/* Utils */
long long	ft_atoll(char *nbr);
int			ft_strlen(char *str);
long		get_timestamp_ms(void);
void		log_message(t_philo *philo, int log_type);
void		my_usleep(long time_ms, t_philo *philo);
/* Validator */
int			is_not_a_valid_sim(t_sim_data *sim, int argc, char **argv);
/* Routine */
void		*routine(void *arg);
int			sim_end(t_sim_data *sim);
/* Mutexes */
int			init_mutexes(t_sim_data *sim, t_philo *philos);
/* Cleaner */
int			clean_all(t_sim_data *sim, t_philo *philos, int exit_status);
/* Simulation */
int			init_sim(t_sim_data *sim, t_philo *philos);

#endif 