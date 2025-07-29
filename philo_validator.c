/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 23:20:20 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/28 20:51:09 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	return_args_err_msg(t_simulation_data *sim, char *arg, int error)
{
	if (error == ARGS_COUNT_ERR)
		write(2, "Usage: ./philo n_philo time_to_die time_to_eat time_to_sleep\n", 62);
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
				write(2, ": negative or null number.\n", 28);
		}
	}
	sim->sim_err = error;
	return (error);
}

int	is_a_valid_number(char *nbr)
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

int	is_not_a_valid_sim(t_simulation_data *sim, int argc, char **argv)
{
	int			i;
	long long	number;

	if (argc != 5)
		return (return_args_err_msg(sim, NULL, ARGS_COUNT_ERR));
	i = 1;
	while (i < argc)
	{
		if (!argv[i] || !argv[i][0])
			return (return_args_err_msg(sim, NULL, ARGS_EMPTY_ERR));
		if (!is_a_valid_number(argv[i]))
			return (return_args_err_msg(sim, argv[i], ARGS_INV_NBR_ERR));
		number = ft_atoll(argv[i]);
		if (number <= 0)
			return (return_args_err_msg(sim, argv[i], ARGS_NEG_NULL_NBR_ERR));
		if (i == 1)
			sim->nbr_of_philosophers = number;
		else if (i == 2)
			sim->time_to_die = number;
		else if (i == 3)
			sim->time_to_eat = number;
		else
			sim->time_to_sleep = number;
		i++;
	}
	return (0);
}
