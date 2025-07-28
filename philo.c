/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 21:44:35 by edgar             #+#    #+#             */
/*   Updated: 2025/07/28 12:26:59 by edfreder         ###   ########.fr       */
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
    int i;

    i = 0;
    if (create_threads(&sim, philos) == THREADS_CREATE_FAIL)
        return (THREADS_CREATE_FAIL);
    i++;
}

// argv[0] -> number_of_philosophers, argv[1] -> time_to_die, argv[2] -> time_to_eat, argv[3] -> time_to_sleep
int main(int argc, char **argv)
{
	t_simulation_data   sim;
    t_philo             *philos;

	memset(&sim, 0, sizeof(t_simulation_data));
    if (is_not_a_valid_sim(argc, argv, &sim))
        return (sim.sim_err);
    philos = malloc(sizeof(t_philo) * sim.nbr_of_philosophers);
    if (!philos)
        return (MEM_FAIL);
    if (create_threads(&sim, philos) == THREADS_CREATE_FAIL)
        return (THREADS_CREATE_FAIL);
    if (init_sim(&sim, philos) != 0)
        return (sim.sim_err); // Limpar philos.
        
}
