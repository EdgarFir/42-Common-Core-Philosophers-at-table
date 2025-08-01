/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 21:44:35 by edgar             #+#    #+#             */
/*   Updated: 2025/07/30 16:39:47 by edfreder         ###   ########.fr       */
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
