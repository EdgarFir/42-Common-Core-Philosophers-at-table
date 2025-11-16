/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitors_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 19:02:43 by edfreder          #+#    #+#             */
/*   Updated: 2025/08/05 13:57:45 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_dead(t_philo *philo)
{
	int	time_diff;

	sem_wait(philo->lm_sem);
	time_diff = get_timestamp_ms() - philo->last_meal_eaten;
	sem_post(philo->lm_sem);
	if (time_diff > philo->sim->time_to_die)
	{
		sem_wait(philo->sim->dead);
		log_message(philo, DEAD);
		return (1);
	}
	return (0);
}

void	*death_monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->f_din_sem);
		if (philo->already_ate == 1)
		{
			sem_post(philo->f_din_sem);
			return (NULL);
		}
		sem_post(philo->f_din_sem);
		if (is_dead(philo))
			exit(1);
		usleep(2000);
	}
	return (NULL);
}
