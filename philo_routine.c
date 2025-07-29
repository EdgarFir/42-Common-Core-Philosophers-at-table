/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:09:01 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/29 23:06:38 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t mutex;

static void time_to_sleep(t_philo *philo)
{
    log_message(philo, SLEEP);
}

static int  is_dead(t_philo *philo)
{
    long    curr_time;

    curr_time = get_timestamp_ms();
    if (!philo->last_time_eated)
        philo->last_time_eated = philo->sim->start_time_ms;
    if (curr_time - philo->last_time_eated > philo->sim->time_to_die)
    {
        pthread_mutex_lock(&philo->dead_mutex);
        philo->died = 1;
        pthread_mutex_unlock(&philo->dead_mutex);
        return (1);
    }
    return (0);
}

static int  time_to_eat(t_philo *philo)
{
    if (is_dead(philo))
        return (-1);
    // Lock first fork
    pthread_mutex_lock(philo->fork1);
    log_message(philo, TAKE_FORK);
    // Lock second fork
    pthread_mutex_lock(philo->fork2);
    log_message(philo, TAKE_FORK);
    log_message(philo, EAT);
    philo->last_time_eated = get_timestamp_ms();
    usleep(philo->sim->time_to_eat * 1000);
    // Passar o tempo
    pthread_mutex_unlock(philo->fork1);
    pthread_mutex_unlock(philo->fork2);
    // Update last time philosopher eated
    // Lock times eated mutex
    pthread_mutex_lock(&philo->times_eated_mutex);
    philo->times_eated++; // Must unlock because monitor(thread) will access this value
    // Unlock times eated mutex
    pthread_mutex_unlock(&philo->times_eated_mutex);
    return (0);
}

int sim_not_end(t_simulation_data *sim)
{
    pthread_mutex_lock(&sim->sim_end_mutex);
    if (sim->sim_end == 1)
    {
        pthread_mutex_unlock(&sim->sim_end_mutex);
        return (1);
    }
    pthread_mutex_unlock(&sim->sim_end_mutex);
    return (0);
}

void    *routine(void *arg)
{
    t_philo         *philo;

    philo = (t_philo *)arg;
    while (!sim_not_end(philo->sim))
    {
        log_message(philo, THINK);
        if (time_to_eat(philo) == -1)
            return (NULL);
        time_to_sleep(philo);
        usleep(philo->sim->time_to_sleep * 1000);
    }
    return (arg);
}