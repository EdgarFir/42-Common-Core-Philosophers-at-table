/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_logger.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 23:56:04 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/29 22:44:16 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_message(t_philo *philo, int log_type)
{
	long	diff_time_ms;

	pthread_mutex_lock(&philo->sim->log_mutex);
	diff_time_ms = get_timestamp_ms() - philo->sim->start_time_ms;
	if (log_type == EAT)
		printf("%li %d is eating\n", diff_time_ms, philo->id);
	else if (log_type == TAKE_FORK)
		printf("%li %d has taken a fork\n", diff_time_ms, philo->id);
	else if (log_type == THINK)
		printf("%li %d is thinking\n", diff_time_ms, philo->id);
	else if (log_type == SLEEP)
		printf("%li %d is sleeping\n", diff_time_ms, philo->id);
	else
		printf("%li %d %sdied%s\n", diff_time_ms, philo->id, RED, RESET);
	pthread_mutex_unlock(&philo->sim->log_mutex);
}