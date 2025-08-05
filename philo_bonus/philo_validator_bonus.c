/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_validator_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 23:20:20 by edfreder          #+#    #+#             */
/*   Updated: 2025/08/05 14:17:18 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	return_args_err_msg(t_sim_data *sim, char *arg, int error)
{
	if (error == ARGS_COUNT_ERR)
		write(2, "Usage: ./philo n_philo time_to_die time_to_eat time_to_sleep \
must_eat_times[optional]\n", 86);
	else
	{
		write(2, "Arguments error: ", 17);
		if (error == ARGS_EMPTY_ERR)
			write(2, "Empty argument/s\n", 18);
		else
		{
			write(2, arg, ft_strlen(arg));
			if (error == ARGS_INV_NBR_ERR)
				write(2, ": invalid number\n", 18);
			else if (error == ARGS_NEG_NULL_NBR_ERR)
				write(2, ": negative or null number\n", 27);
			else if (error == NBR_PHILOS_ERR)
				write(2, ": number of philos must be between 1 and 200\n", 46);
			else if (error == TIME_MIN_VALUE_ERROR)
				write(2, ": time must be higher or equal than 60 ms\n", 34);
		}
	}
	sim->sim_err = error;
	return (error);
}

static int	is_a_valid_number(char *nbr)
{
	int	i;

	i = 0;
	while ((nbr[i] >= 9 && nbr[i] <= 13) || nbr[i] == 32)
		i++;
	if (nbr[i] == '-' || nbr[i] == '+')
		i++;
	while (nbr[i])
	{
		if (nbr[i] < '0' || nbr[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static void	add_sim_data(t_sim_data *sim, int argv_index, int value)
{
	if (argv_index == 1)
		sim->philo_c = value;
	else if (argv_index == 2)
		sim->time_to_die = value;
	else if (argv_index == 3)
		sim->time_to_eat = value;
	else if (argv_index == 4)
		sim->time_to_sleep = value;
	else
		sim->must_eat_times = value;
}

int	is_not_a_valid_sim(t_sim_data *sim, int argc, char **argv)
{
	int			i;
	long long	value;

	if (argc != 5 && argc != 6)
		return (return_args_err_msg(sim, NULL, ARGS_COUNT_ERR));
	i = 1;
	while (i < argc)
	{
		if (!argv[i] || !argv[i][0])
			return (return_args_err_msg(sim, NULL, ARGS_EMPTY_ERR));
		if (!is_a_valid_number(argv[i]))
			return (return_args_err_msg(sim, argv[i], ARGS_INV_NBR_ERR));
		value = ft_atoll(argv[i]);
		if (value <= 0)
			return (return_args_err_msg(sim, argv[i], ARGS_NEG_NULL_NBR_ERR));
		if (i == 1 && value > 200)
			return (return_args_err_msg(sim, argv[i], NBR_PHILOS_ERR));
		else if (i > 1 && i <= 4 && value < 60)
			return (return_args_err_msg(sim, argv[i], TIME_MIN_VALUE_ERROR));
		add_sim_data(sim, i, value);
		i++;
	}
	return (0);
}

void	set_dinner_end(t_philo *philo)
{
	sem_wait(philo->f_din_sem);
	philo->already_ate = 1;
	sem_post(philo->f_din_sem);
	exit(0);
}
