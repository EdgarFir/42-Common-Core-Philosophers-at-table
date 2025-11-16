/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:09:01 by edfreder          #+#    #+#             */
/*   Updated: 2025/08/05 12:11:32 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sim_end(t_sim_data *sim)
{
	pthread_mutex_lock(&sim->sim_end_mutex);
	if (sim->sim_end == 1)
	{
		pthread_mutex_unlock(&sim->sim_end_mutex);
		return (1);
	}
	pthread_mutex_unlock(&sim->sim_end_mutex);
	return (0);
}

static void	time_to_sleep(t_philo *philo)
{
	if (sim_end(philo->sim))
		return ;
	log_message(philo, SLEEP);
	my_usleep(philo->sim->time_to_sleep, philo);
}

int	ate_all_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->times_eated_mutex);
	if (philo->sim->must_eat_times
		&& philo->sim->must_eat_times == philo->times_eated)
	{
		pthread_mutex_unlock(&philo->times_eated_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->times_eated_mutex);
	return (0);
}

static int	time_to_eat(t_philo *philo)
{
	if (sim_end(philo->sim))
		return (-1);
	pthread_mutex_lock(philo->fork1);
	log_message(philo, TAKE_FORK);
	pthread_mutex_lock(philo->fork2);
	log_message(philo, TAKE_FORK);
	log_message(philo, EAT);
	pthread_mutex_lock(&philo->last_time_eated_mutex);
	philo->last_time_eated = get_timestamp_ms();
	pthread_mutex_unlock(&philo->last_time_eated_mutex);
	my_usleep(philo->sim->time_to_eat, philo);
	pthread_mutex_unlock(philo->fork1);
	pthread_mutex_unlock(philo->fork2);
	pthread_mutex_lock(&philo->times_eated_mutex);
	philo->times_eated++;
	if (philo->sim->must_eat_times
		&& philo->times_eated == philo->sim->must_eat_times)
	{
		pthread_mutex_unlock(&philo->times_eated_mutex);
		return (-1);
	}
	pthread_mutex_unlock(&philo->times_eated_mutex);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(philo->sim->time_to_eat * 1000);
	while (!sim_end(philo->sim))
	{
		if (sim_end(philo->sim) || ate_all_meals(philo))
			return (NULL);
		if (!sim_end(philo->sim))
			log_message(philo, THINK);
		if (philo->sim->nbr_of_philosophers == 1)
			return (NULL);
		if (time_to_eat(philo) == -1)
			return (NULL);
		if (sim_end(philo->sim))
			break ;
		if (!sim_end(philo->sim))
			time_to_sleep(philo);
		if (sim_end(philo->sim))
			break ;
		if (philo->sim->nbr_of_philosophers % 2 && !sim_end(philo->sim))
			my_usleep(philo->sim->time_to_eat, philo);
	}
	return (arg);
}
