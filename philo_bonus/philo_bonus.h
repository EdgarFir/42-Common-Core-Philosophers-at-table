/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 00:32:02 by edfreder          #+#    #+#             */
/*   Updated: 2025/08/01 13:07:58 by edfreder         ###   ########.fr       */
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
# define NBR_PHILOS_ERR 5
# define TIME_MIN_VALUE_ERROR 6
# define MEM_FAIL 7
# define THREADS_FINISH_FAIL 8
# define THREADS_CREATE_FAIL 9
# define MUTEX_INIT_FAIL 10

typedef struct	s_simulation_data
{
	int				nbr_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_times;
	int				sim_err;
	int				sim_end;
	long			start_time_ms;
} t_simulation_data;


int	is_not_a_valid_sim(t_simulation_data *sim, int argc, char **argv);

#endif