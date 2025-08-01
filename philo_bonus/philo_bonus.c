/*
	memset, printf, malloc, free, write
	fork, kill, exit
	pthread_create, pthread_detach, pthread_join,
	usleep, gettimeofday
	waitpid
	sem_open, sem_close, sem_post, sem_wait, sem_unlink
*/

#include "philo_bonus.h"

int main(int argc, char **argv)
{
	t_simulation_data   sim;

	memset(&sim, 0, sizeof(t_simulation_data));
    if (is_not_a_valid_sim(&sim, argc, argv))
        return (sim.sim_err);
	// Vou precisar de um array de pids, e de um semaforo global
	// Esse semaforo vai fazer o gerenciamento de acesso a recursos
	// O semaforo 
}