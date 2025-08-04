/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_semaphores_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 23:11:09 by edfreder          #+#    #+#             */
/*   Updated: 2025/08/02 23:34:32 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	unlink_sim_semaphores(void)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/dead");
	sem_unlink("/eat_c");
}

void	close_sim_semaphores(t_simulation_data *sim)
{
	sem_close(sim->forks);
	sem_close(sim->print);
	sem_close(sim->dead);
	sem_close(sim->eat_c);
}

void	init_sim_semaphores(t_simulation_data *sim)
{
	unlink_sim_semaphores();
	sim->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, sim->philo_c);
	sim->print = sem_open("/print", O_CREAT | O_EXCL, 0644, 1);
	sim->dead = sem_open("/dead", O_CREAT | O_EXCL, 0644, 1);
	sim->eat_c = sem_open("/eat_c", O_CREAT | O_EXCL, 0644, sim->philo_c / 2);
	if (sim->forks == SEM_FAILED || sim->print == SEM_FAILED
		|| sim->dead == SEM_FAILED || sim->eat_c == SEM_FAILED)
		exit (errno);
}

void	open_philo_semaphores(t_philo *philo)
{
	philo->lm_sem_name = get_sem_name("/l_meal", philo);
	sem_unlink(philo->lm_sem_name);
	philo->lm_sem = sem_open(philo->lm_sem_name, O_CREAT | O_EXCL, 0644, 1);
}
