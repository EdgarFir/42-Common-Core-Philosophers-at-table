/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:09:01 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/29 01:40:59 by edfreder         ###   ########.fr       */
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
    if (curr_time - philo->sim->start_time_ms > philo->sim->time_to_die)
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
    // Check if actual time - last meal time not higher than time to die, else is dead
   
    // Take the forks
    pthread_mutex_lock(philo->fork1);
    pthread_mutex_lock(philo->fork2);
    log_message(philo, EAT);
    pthread_mutex_unlock(philo->fork1);
    pthread_mutex_unlock(philo->fork2);
    // Update last time philosopher eated
    philo->last_time_eated = get_timestamp_ms();
    // Lock times eated mutex
    pthread_mutex_lock(&philo->times_eated_mutex);
    philo->times_eated++; // Must unlock because monitor(thread) will access this value
    // Unlock times eated mutex
    pthread_mutex_unlock(&philo->times_eated_mutex);
    return (0);
}

void    *routine(void *arg)
{
    t_philo         *philo;

    philo = (t_philo *)arg;
    log_message(philo, THINK);
    if (time_to_eat(philo) == -1)
        return (NULL);
    time_to_sleep(philo);
    return (arg);
}