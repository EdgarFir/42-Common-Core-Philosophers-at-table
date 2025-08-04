/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 00:04:42 by edfreder          #+#    #+#             */
/*   Updated: 2025/08/03 00:09:51 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	exit_and_clean(t_simulation_data *sim, t_philo *philos, int exstatus, int unlink)
{
	int	i;

	i = 0;
	if (unlink)
	{
		close_sim_semaphores(sim);
		unlink_sim_semaphores();
	}
	while (i < sim->philo_c)
	{
		if (unlink)
		{
			sem_close(philos[i].lm_sem);
			if (philos[i].lm_sem_name)
				sem_unlink(philos[i].lm_sem_name);
		}
		if (philos[i].lm_sem_name)
			free(philos[i].lm_sem_name);
		i++;
	}
	free(philos);
	exit(exstatus);
}

int main(int argc, char **argv)
{
	t_simulation_data   sim;
	t_philo				*philos;

	memset(&sim, 0, sizeof(t_simulation_data));
    if (is_not_a_valid_sim(&sim, argc, argv))
		return (sim.sim_err);
	init_sim_semaphores(&sim);
	philos = malloc(sizeof(t_philo) * sim.philo_c);
	if (!philos)
		exit(MEM_FAIL);
	memset(philos, 0, sizeof(t_philo) * sim.philo_c);
	sim.philos = philos;
	init_sim(&sim, philos);
	exit_and_clean(&sim, philos, 0, 1);
}
