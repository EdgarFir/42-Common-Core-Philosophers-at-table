/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 21:44:35 by edgar             #+#    #+#             */
/*   Updated: 2025/07/29 23:54:26 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
    memset, printf, malloc, free, write,
    usleep, gettimeofday
    pthread_create, pthread_detach, pthread_join
    pthread_mutex_init, pthread_mutex_destroy,
    pthread_mutex_lock, pthread_mutex_unlock
*/

#include "philo.h"

void    *monitor(void *arg)
{
    t_philo *philos;
    int     i;
    int     nbr_of_philos;

    philos = (t_philo *)arg;
    i = 0;
    nbr_of_philos = philos->sim->nbr_of_philosophers;
    while (1)
    {
        pthread_mutex_lock(&philos[i % nbr_of_philos].dead_mutex);
        if (philos[i % nbr_of_philos].died == 1)
        {
            pthread_mutex_unlock(&philos[i % nbr_of_philos].dead_mutex);
            pthread_mutex_lock(&philos->sim->sim_end_mutex);
            philos->sim->sim_end = 1;
            pthread_mutex_unlock(&philos->sim->sim_end_mutex);
            log_message(&philos[i % nbr_of_philos], DEAD);
            break ;
        }
        pthread_mutex_unlock(&philos[i % nbr_of_philos].dead_mutex);
        i++;
    }
    return (arg);
}

int init_sim(t_simulation_data *sim, t_philo *philos)
{
    sim->start_time_ms = get_timestamp_ms();
    if (create_threads(sim, philos) == THREADS_CREATE_FAIL)
        return (THREADS_CREATE_FAIL);
    if (pthread_create(&sim->monitor_th, NULL, &monitor, &philos[0]) != 0)
       return (THREADS_CREATE_FAIL);
    sim->monitor_thread_initialized = 1;
    return (0);
}

int main(int argc, char **argv)
{
	t_simulation_data   sim;
    t_philo             *philos;

	memset(&sim, 0, sizeof(t_simulation_data));
    if (is_not_a_valid_sim(&sim, argc, argv))
        return (sim.sim_err);
    philos = malloc(sizeof(t_philo) * sim.nbr_of_philosophers);
    if (!philos)
        return (MEM_FAIL);
    memset(philos, 0, sizeof(t_philo) * sim.nbr_of_philosophers);
    if (init_mutexes(&sim, philos) != 0)
        return (clean_all(&sim, philos, sim.sim_err));
    if (init_sim(&sim, philos) != 0)
        return (clean_all(&sim, philos, sim.sim_err));
    return (clean_all(&sim, philos, 0));
}
