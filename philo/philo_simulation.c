/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 00:07:10 by edfreder          #+#    #+#             */
/*   Updated: 2025/08/05 12:41:16 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_dead(t_philo *philo)
{
	long	curr_time;

	pthread_mutex_lock(&philo->times_eated_mutex);
	if (philo->sim->must_eat_times
		&& (philo->sim->must_eat_times == philo->times_eated))
	{
		pthread_mutex_unlock(&philo->times_eated_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->times_eated_mutex);
	curr_time = get_timestamp_ms();
	pthread_mutex_lock(&philo->last_time_eated_mutex);
	if (!philo->last_time_eated)
		philo->last_time_eated = philo->sim->start_time_ms;
	if (curr_time - philo->last_time_eated > philo->sim->time_to_die)
	{
		pthread_mutex_unlock(&philo->last_time_eated_mutex);
		pthread_mutex_lock(&philo->dead_mutex);
		philo->died = 1;
		pthread_mutex_unlock(&philo->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->last_time_eated_mutex);
	return (0);
}

int	all_ate(t_philo *philos, int must_eat_times)
{
	int	nbr_of_philos;
	int	i;

	if (!must_eat_times)
		return (0);
	nbr_of_philos = philos->sim->nbr_of_philosophers;
	i = 0;
	while (i < nbr_of_philos)
	{
		pthread_mutex_lock(&philos[i].times_eated_mutex);
		if (philos[i].times_eated != must_eat_times)
		{
			pthread_mutex_unlock(&philos[i].times_eated_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philos[i].times_eated_mutex);
		i++;
	}
	return (1);
}

static void	*monitor(void *arg)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)arg;
	i = 0;
	while (1)
	{
		if (all_ate(&philos[0], philos->sim->must_eat_times))
		{
			set_sim_end(philos->sim);
			return (NULL);
		}
		if (is_dead(&philos[i % philos->sim->nbr_of_philosophers]))
		{
			set_sim_end(philos->sim);
			log_message(&philos[i % philos->sim->nbr_of_philosophers], DEAD);
			return (NULL);
		}
		usleep(100);
		i++;
	}
	return (arg);
}

static void	sit_philos_at_table(t_sim_data *sim, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < sim->nbr_of_philosophers)
	{
		philos[i].id = i + 1;
		philos[i].sim = sim;
		if (i == 0)
		{
			philos[i].fork1 = &sim->forks[i];
			philos[i].fork2 = &sim->forks[sim->nbr_of_philosophers - 1];
		}
		else if (i != sim->nbr_of_philosophers - 1)
		{
			philos[i].fork1 = &sim->forks[i];
			philos[i].fork2 = &sim->forks[i - 1];
		}
		else
		{
			philos[i].fork1 = &sim->forks[i - 1];
			philos[i].fork2 = &sim->forks[i];
		}
		i++;
	}
}

int	init_sim(t_sim_data *sim, t_philo *philos)
{
	int	i;

	sit_philos_at_table(sim, philos);
	sim->start_time_ms = get_timestamp_ms();
	i = 0;
	while (i < sim->nbr_of_philosophers)
	{
		if (pthread_create(&philos[i].th, NULL, &routine, &philos[i]) != 0)
			return (THREADS_CREATE_FAIL);
		philos[i].thread_initialized = 1;
		i++;
	}
	if (pthread_create(&sim->monitor_th, NULL, &monitor, philos) != 0)
		return (THREADS_CREATE_FAIL);
	sim->monitor_thread_initialized = 1;
	return (0);
}
