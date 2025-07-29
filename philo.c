/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 21:44:35 by edgar             #+#    #+#             */
/*   Updated: 2025/07/29 01:38:11 by edfreder         ###   ########.fr       */
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

int init_sim(t_simulation_data *sim, t_philo *philos)
{
    sim->start_time_ms = get_timestamp_ms();
    // Start monitor
    // Start philosophers threads
    if (create_threads(sim, philos) == THREADS_CREATE_FAIL)
        return (THREADS_CREATE_FAIL);
    return (0);
}

int init_fork_mutexes(t_simulation_data *sim)
{
    int i;

    sim->forks = malloc(sizeof(pthread_mutex_t) * sim->nbr_of_philosophers);
    if (!sim->forks)
    {
        sim->sim_err = MEM_FAIL;
        return (MEM_FAIL);
    }
    i = 0;
    while (i < sim->nbr_of_philosophers)
    {
        if (pthread_mutex_init(&sim->forks[i], NULL) != 0)
        {
            sim->sim_err = MUTEX_INIT_FAIL;
            return (MUTEX_INIT_FAIL);
        }
        i++;
    }
    return (0);
}

// argv[0] -> number_of_philosophers, argv[1] -> time_to_die, argv[2] -> time_to_eat, argv[3] -> time_to_sleep
int main(int argc, char **argv)
{
	t_simulation_data   sim;
    t_philo             *philos;

	memset(&sim, 0, sizeof(t_simulation_data));
    if (is_not_a_valid_sim(&sim, argc, argv))
        return (sim.sim_err);
    if (init_fork_mutexes(&sim) != 0)
        return (sim.sim_err);
    // List of mutex to init
    pthread_mutex_init(&sim.log_mutex, NULL);
    philos = malloc(sizeof(t_philo) * sim.nbr_of_philosophers);
    if (!philos)
        return (MEM_FAIL);
    if (init_threads_mutexes(philos, sim.nbr_of_philosophers) != 0)
        return (MUTEX_INIT_FAIL);
    if (init_sim(&sim, philos) != 0)
        return (sim.sim_err);
    for (int i = 0; i < sim.nbr_of_philosophers; i++)
        finish_thread(philos[i].th);
    // Destroy list of mutexes
    pthread_mutex_destroy(&sim.log_mutex);
    // Destroy main mutexes
    for (int i = 0; i < sim.nbr_of_philosophers; i++)
    {
        pthread_mutex_destroy(&sim.forks[i]);
        pthread_mutex_destroy(&philos[i].dead_mutex);
        pthread_mutex_destroy(&philos[i].times_eated_mutex);
    }
    // Kill threads
    return (0);
}
