/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgar <edfreder@student.42porto.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 21:44:35 by edgar             #+#    #+#             */
/*   Updated: 2025/07/25 21:50:30 by edgar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
    memset, printf, malloc, free, write,
    usleep, gettimeofday
    pthread_create, pthread_detach, pthread_join
    pthread_mutex_init, pthread_mutex_destroy,
    pthread_mutex_lock, pthread_mutex_unlock
*/

#include "philo.h"

// argv[0] -> number_of_philosophers, argv[1] -> time_to_die, argv[2] -> time_to_eat, argv[3] -> time_to_sleep
int main(int argc, char **argv)
{
    if (argc != 5)
    {
        write(2, "Usage: ./philo n_philo time_to_die time_to_eat time_to_sleep\n", 62);
        return (ARGSERR);
    }
    // Start threads
    // 
}