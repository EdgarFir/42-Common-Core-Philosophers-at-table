/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 22:45:58 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/29 23:55:35 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int init_fork_mutexes(t_simulation_data *sim)
{
    sim->forks = malloc(sizeof(pthread_mutex_t) * sim->nbr_of_philosophers);
    if (!sim->forks)
    {
        sim->sim_err = MEM_FAIL;
        return (MEM_FAIL);
    }
    while (sim->forks_initialized < sim->nbr_of_philosophers)
    {
        if (pthread_mutex_init(&sim->forks[sim->forks_initialized], NULL) != 0)
        {
            sim->sim_err = MUTEX_INIT_FAIL;
            return (MUTEX_INIT_FAIL);
        }
        sim->forks_initialized++;
    }
    return (0);
}

static int init_sim_mutexes(t_simulation_data *sim)
{
    if (pthread_mutex_init(&sim->log_mutex, NULL) != 0)
        return (MUTEX_INIT_FAIL);
    sim->log_mutex_initialized = 1;
    if (pthread_mutex_init(&sim->sim_end_mutex, NULL) != 0)
        return (MUTEX_INIT_FAIL);
    sim->sim_end_mutex_initialized = 1;
    return (0);
}

static int init_philos_mutexes(t_philo *philos, int philos_count)
{
    int i;

    i = 0;
    while (i < philos_count)
    {
        if (pthread_mutex_init(&philos[i].dead_mutex, NULL) == -1)
            return (MUTEX_INIT_FAIL);
        philos[i].dead_mutex_initialized = 1;
        if (pthread_mutex_init(&philos[i].times_eated_mutex, NULL) == -1)
            return (MUTEX_INIT_FAIL);
        philos[i].times_eated_mutex_initialized = 1;
        i++;
    }
    return (0);
}

int	init_mutexes(t_simulation_data *sim, t_philo *philos)
{
    int init_status;

    init_status = init_fork_mutexes(sim);
    if (init_status != 0)
        return (init_status);
    init_status = init_sim_mutexes(sim);
    if (init_status != 0)
        return (init_status);
    init_status = init_philos_mutexes(philos, sim->nbr_of_philosophers);
    if (init_status != 0)
        return (init_status);
    return (0);
}
