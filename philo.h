/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 21:45:19 by edgar             #+#    #+#             */
/*   Updated: 2025/07/28 12:27:55 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H
# define ARGS_COUNT_ERR 1
# define ARGS_EMPTY_ERR 2
# define ARGS_INV_NBR_ERR 3
# define ARGS_NEG_NULL_NBR_ERR 4
# define MEM_FAIL 5
# define THREADS_FINISH_FAIL 6
# define THREADS_CREATE_FAIL 7

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

typedef struct	s_philo
{
	int					id;
	pthread_t			th;
	t_simulation_data	*sim;
} t_philo;	

typedef struct	s_simulation_data
{
	int nbr_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int sim_err;
	int test_sum;
} t_simulation_data;

/* Utils */
long long	ft_atoll(char *nbr);
int			ft_strlen(char *str);
/* Validator */
int			is_not_a_valid_sim(int argc, char **argv, t_simulation_data *sim);
/* Threads */
int			create_threads(t_simulation_data *data, t_philo *philos);
int			finish_thread(pthread_t thread);
/* Routine */
void 		*routine(void *arg);

#endif 