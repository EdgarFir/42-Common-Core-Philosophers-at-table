/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sem_name_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 01:24:57 by edfreder          #+#    #+#             */
/*   Updated: 2025/08/02 18:59:53 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static char	*ft_itoa(int nbr)
{
	int		nbr_len;
	int		tmp_nbr;
	char	*chr_nbr;

	tmp_nbr = nbr;
	nbr_len = 0;
	while (tmp_nbr)
	{
		nbr_len++;
		tmp_nbr /= 10;
	}
	chr_nbr = malloc(sizeof(char) * (nbr_len + 1));
	if (!chr_nbr)
		exit(MEM_FAIL);
	chr_nbr[nbr_len] = '\0';
	while (nbr_len > 0)
	{
		chr_nbr[nbr_len - 1] = '0' + (nbr % 10);
		nbr /= 10;
		nbr_len--;
	}
	return (chr_nbr);
}

static char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		s1_len;
	int		s2_len;
	char	*joined;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	joined = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!joined)
		exit(MEM_FAIL);
	i = 0;
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		joined[s1_len + i] = s2[i];
		i++;
	}
	joined[s1_len + s2_len] = '\0';
	return (joined);
}

char	*get_sem_name(char *sem_type, t_philo *philo)
{
	char	*id;
	char	*sem_name;

	id = ft_itoa(philo->id);
	if (!id)
		exit(MEM_FAIL);
	sem_name = ft_strjoin(sem_type, id);
	free(id);
	if (!sem_name)
		exit(MEM_FAIL);
	return (sem_name);
}