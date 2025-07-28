/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:28:31 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/28 12:25:57 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int finish_thread(pthread_t thread)
{
    if (pthread_join(thread, NULL) != 0)
        return (THREADS_FINISH_FAIL);
    return (0);
}

// pthread_create, pthread_detach, pthread_join
int create_threads(t_simulation_data *sim, t_philo *philos)
{
    int i;

    i = 0;
    while (i < sim->nbr_of_philosophers)
    {
        philos->id = i + 1;
        philos->sim = sim;
        if (pthread_create(philos->th, NULL, &routine, &philos[i]) != 0)
            return (THREADS_CREATE_FAIL);
        i++;
    }
}
