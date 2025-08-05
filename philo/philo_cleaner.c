/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cleaner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 23:09:41 by edfreder          #+#    #+#             */
/*   Updated: 2025/08/04 22:36:26 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_sim_mutexes(t_sim_data *sim)
{
	int	i;

	if (sim->sim_end_mutex_initialized == 1)
		pthread_mutex_destroy(&sim->sim_end_mutex);
	if (sim->log_mutex_initialized == 1)
		pthread_mutex_destroy(&sim->log_mutex);
	if (sim->forks)
	{
		i = 0;
		while (i < sim->forks_initialized)
		{
			pthread_mutex_destroy(&sim->forks[i]);
			i++;
		}
		free(sim->forks);
	}
}

void	destroy_philos_mutexes(t_philo *philos)
{
	int	i;

	if (!philos)
		return ;
	i = 0;
	while (i < philos->sim->nbr_of_philosophers)
	{
		if (philos[i].dead_mutex_initialized == 1)
			pthread_mutex_destroy(&philos[i].dead_mutex);
		if (philos[i].times_eated_mutex_initialized == 1)
			pthread_mutex_destroy(&philos[i].times_eated_mutex);
		if (philos[i].last_time_eated_mutex_initialized == 1)
			pthread_mutex_destroy(&philos[i].last_time_eated_mutex);
		i++;
	}
}

void	clean_philos(t_philo *philos, int philos_count)
{
	int	i;

	if (!philos)
		return ;
	i = 0;
	while (i < philos_count)
	{
		if (philos[i].thread_initialized == 1)
			pthread_join(philos[i].th, NULL);
		i++;
	}
}

int	clean_all(t_sim_data *sim, t_philo *philos, int exit_status)
{
	clean_philos(philos, sim->nbr_of_philosophers);
	if (sim->monitor_thread_initialized == 1)
		pthread_join(sim->monitor_th, NULL);
	destroy_sim_mutexes(sim);
	destroy_philos_mutexes(philos);
	free(philos);
	return (exit_status);
}
