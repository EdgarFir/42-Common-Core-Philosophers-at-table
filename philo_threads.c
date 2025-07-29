/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:28:31 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/29 01:29:05 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int finish_thread(pthread_t thread)
{
    if (pthread_join(thread, NULL) != 0)
        return (THREADS_FINISH_FAIL);
    return (0);
}

int init_threads_mutexes(t_philo *philos, int nbr_of_philos)
{
    int i;

    i = 0;
    while (i < nbr_of_philos)
    {
        if (pthread_mutex_init(&philos[i].dead_mutex, NULL) != 0)
            return (MUTEX_INIT_FAIL);
        if (pthread_mutex_init(&philos[i].times_eated_mutex, NULL) != 0)
            return (MUTEX_INIT_FAIL);
        i++;
    }
    return (0);
}

// pthread_create, pthread_detach, pthread_join
int create_threads(t_simulation_data *sim, t_philo *philos)
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
        if (pthread_create(&philos[i].th, NULL, &routine, &philos[i]) != 0)
            return (THREADS_CREATE_FAIL);
        i++;
    }
    return (0);
}
