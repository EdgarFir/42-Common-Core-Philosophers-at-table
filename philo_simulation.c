/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 00:07:10 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/30 19:12:36 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int create_threads(t_simulation_data *sim, t_philo *philos)
{
    int i;

    i = 0;
    while (i < sim->nbr_of_philosophers)
    {
        if (pthread_create(&philos[i].th, NULL, &routine, &philos[i]) != 0)
            return (THREADS_CREATE_FAIL);
        philos[i].thread_initialized = 1;
        i++;
    }
    return (0);
}

static int  is_dead(t_philo *philo)
{
    long    curr_time;

    curr_time = get_timestamp_ms();
    pthread_mutex_lock(&philo->last_time_eated_mutex);
    if (!philo->last_time_eated)
        philo->last_time_eated = philo->sim->start_time_ms;
    if (curr_time - philo->last_time_eated > philo->sim->time_to_die)
    {
        pthread_mutex_unlock(&philo->last_time_eated_mutex);
        pthread_mutex_lock(&philo->dead_mutex);
        philo->died = 1;
        pthread_mutex_unlock(&philo->dead_mutex);
        return (1);
    }
    pthread_mutex_unlock(&philo->last_time_eated_mutex);
    return (0);
}

static void    *monitor(void *arg)
{
    t_philo *philos;
    int     i;
    int     max_index;

    philos = (t_philo *)arg;
    i = 0;
    max_index = philos->sim->nbr_of_philosophers;
    while (1)
    {
        if (is_dead(&philos[i % max_index]))
        {
            pthread_mutex_lock(&philos->sim->sim_end_mutex);
            philos->sim->sim_end = 1;
            pthread_mutex_unlock(&philos->sim->sim_end_mutex);
            log_message(&philos[i % max_index], DEAD);
            return (NULL);
        }
        i++;
        usleep(10);
    }
    return (arg);
}

void    sit_philos_at_table(t_simulation_data *sim, t_philo *philos)
{
    int i;

    i = 0;
    while (i < sim->nbr_of_philosophers)
    {
        philos[i].id = i + 1;
        philos[i].sim = sim;
        if (i != sim->nbr_of_philosophers - 1)
        {
            philos[i].fork1 = &sim->forks[i];
            philos[i].fork2 = &sim->forks[i + 1];
        }
        else
        {
            philos[i].fork1 = &sim->forks[(i + 1) % sim->nbr_of_philosophers];
            philos[i].fork2 = &sim->forks[i];
        }
        i++;
    }
}

int init_sim(t_simulation_data *sim, t_philo *philos)
{
    sit_philos_at_table(sim, philos);
    sim->start_time_ms = get_timestamp_ms();
    if (create_threads(sim, philos) == THREADS_CREATE_FAIL)
        return (THREADS_CREATE_FAIL);
    if (pthread_create(&sim->monitor_th, NULL, &monitor, philos) != 0)
       return (THREADS_CREATE_FAIL);
    sim->monitor_thread_initialized = 1;
    return (0);
}
