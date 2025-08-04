/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 00:32:02 by edfreder          #+#    #+#             */
/*   Updated: 2025/08/02 19:40:04 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H

# define PHILO_BONUS_H

#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>

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
# define NBR_PHILOS_ERR 5
# define TIME_MIN_VALUE_ERROR 6
# define MEM_FAIL 7
# define SEM_INIT_ERR 8

struct s_philo;

typedef struct	s_simulation_data
{
	int				philo_c;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_times;
	int				sim_err;
	long			start_time_ms;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*dead;
	sem_t			*eat_c;
	struct s_philo	*philos;
} t_simulation_data;

typedef struct	s_philo
{
	int					id;
	int					died;
	int					already_ate;
	int					meals_count;
	long				last_meal_eaten;
	char				*lm_sem_name;
	char				*mc_sem_name;
	pid_t				philo_pid;
	sem_t				*lm_sem;
	sem_t				*mc_sem; 
	t_simulation_data	*sim;
} t_philo;

/* Utils */
long long	ft_atoll(char *nbr);
int			ft_strlen(char *str);
long		get_timestamp_ms(void);
void		log_message(t_philo *philo, int log_type);
void		my_usleep(long time_ms);
/* Semaphores */
void		init_sim_semaphores(t_simulation_data *sim);
void		close_sim_semaphores(t_simulation_data *sim);
void		unlink_sim_semaphores(void);
void		open_philo_semaphores(t_philo *philo);
/* Validator */
int			is_not_a_valid_sim(t_simulation_data *sim, int argc, char **argv);
/* Simulation */
void		init_sim(t_simulation_data *sim, t_philo *philos);
void		exit_and_clean(t_simulation_data *sim, t_philo *philos, int exstatus, int unlink);
/* Sem_name */
char		*get_sem_name(char *sem_type, t_philo *philo);
/* Monitors */
void		*death_monitor(void *arg);

#endif