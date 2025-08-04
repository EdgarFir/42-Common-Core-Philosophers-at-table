/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 00:25:07 by edfreder          #+#    #+#             */
/*   Updated: 2025/08/02 16:06:18 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	log_message(t_philo *philo, int log_type)
{
	long	diff_time_ms;

	sem_wait(philo->sim->print);
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
	if (log_type != DEAD)
		sem_post(philo->sim->print);
}

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

long long	ft_atoll(char *nbr)
{
	long long	result;
	int			i;
	int			signal;

	result = 0;
	i = 0;
	signal = 1;
	while ((nbr[i] >= 9 && nbr[i] <= 13) || nbr[i] == 32)
		i++;
	if (nbr[i] == '-' || nbr[i] == '+')
	{
		if (nbr[i] == '-')
			signal = -signal;
		i++;
	}
	while (nbr[i] >= '0' && nbr[i] <= '9')
	{
		result = result * 10 + (nbr[i] - '0');
		i++;
	}
	return (result * signal);
}

long	get_timestamp_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void my_usleep(long time_ms)
{
	long start;

	start = get_timestamp_ms();
	while (get_timestamp_ms() - start < time_ms)
		usleep(100);
}
