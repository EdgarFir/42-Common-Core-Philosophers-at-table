/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:28:31 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/29 23:52:15 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


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
        philos[i].thread_initialized = 1;
        i++;
    }
    return (0);
}
