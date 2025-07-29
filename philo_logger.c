/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_logger.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 23:56:04 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/29 00:30:14 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_message(t_philo *philo, int log_type)
{
	pthread_mutex_lock(&philo->sim->log_mutex);
	if (log_type == EAT)
		printf("%d is eating\n", philo->id);
	else if (log_type == TAKE_FORK)
		printf("%d has taken a fork\n", philo->id);
	else if (log_type == THINK)
		printf("%d is thinking\n", philo->id);
	else if (log_type == SLEEP)
		printf("%d is sleeping\n", philo->id);
	else
		printf("%d died\n", philo->id);
	pthread_mutex_unlock(&philo->sim->log_mutex);
}