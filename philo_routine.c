/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:09:01 by edfreder          #+#    #+#             */
/*   Updated: 2025/07/28 12:29:40 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t mutex;

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    pthread_mutex_lock(&mutex);
    
    return (arg);
}