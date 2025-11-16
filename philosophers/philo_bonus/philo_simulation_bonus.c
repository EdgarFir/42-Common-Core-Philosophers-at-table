/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simulation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 23:10:11 by edfreder          #+#    #+#             */
/*   Updated: 2025/08/05 14:17:02 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	eat(t_sim_data *sim, t_philo *philo)
{
	sem_wait(sim->forks);
	log_message(philo, TAKE_FORK);
	if (sim->philo_c == 1)
	{
		sem_wait(philo->sim->dead);
		log_message(philo, DEAD);
		exit(0);
	}
	sem_wait(sim->forks);
	log_message(philo, TAKE_FORK);
	log_message(philo, EAT);
	sem_wait(philo->lm_sem);
	philo->last_meal_eaten = get_timestamp_ms();
	sem_post(philo->lm_sem);
	my_usleep(sim->time_to_eat);
	philo->meals_count++;
	sem_post(sim->forks);
	sem_post(sim->forks);
}

static int	exec_son(t_sim_data *sim, t_philo *philo)
{
	pthread_t	thread;

	philo->philo_pid = fork();
	if (philo->philo_pid == -1)
		return (-1);
	else if (philo->philo_pid == 0)
	{
		if (pthread_create(&thread, NULL, &death_monitor, philo) != 0)
			exit(errno);
		pthread_detach(thread);
		while (1)
		{
			log_message(philo, THINK);
			sem_wait(sim->eat_c);
			eat(sim, philo);
			sem_post(sim->eat_c);
			if (sim->must_eat_times
				&& sim->must_eat_times == philo->meals_count)
				set_dinner_end(philo);
			log_message(philo, SLEEP);
			my_usleep(sim->time_to_sleep);
		}
	}
	return (0);
}

static void	wait_for_some_philo_dead(t_philo *philos, int philo_c)
{
	pid_t	dead_pid;
	int		status;
	int		i;

	dead_pid = waitpid(-1, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		i = 0;
		while (i < philo_c)
		{
			if (dead_pid != philos[i].philo_pid)
				kill(philos[i].philo_pid, SIGKILL);
			i++;
		}
	}
}

static void	wait_for_all_philos(t_philo *philos, int philo_c)
{
	int	i;

	i = 0;
	while (i < philo_c)
	{
		waitpid(philos[i].philo_pid, NULL, 0);
		i++;
	}
}

void	init_sim(t_sim_data *sim, t_philo *philos)
{
	int		i;

	i = 0;
	sim->start_time_ms = get_timestamp_ms();
	while (i < sim->philo_c)
	{
		philos[i].last_meal_eaten = sim->start_time_ms;
		philos[i].sim = sim;
		philos[i].id = i + 1;
		open_philo_semaphores(&philos[i]);
		if (exec_son(sim, &philos[i]) == -1)
			exit_clean(sim, philos, errno);
		i++;
	}
	wait_for_some_philo_dead(philos, sim->philo_c);
	wait_for_all_philos(philos, sim->philo_c);
}
