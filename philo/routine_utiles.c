/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utiles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaras <bfaras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 09:36:34 by bfaras            #+#    #+#             */
/*   Updated: 2025/08/12 09:36:50 by bfaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		usleep(300);
	while (check_loob(philo))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	*routine_one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	return (NULL);
}

void	one_philo_t(t_philo *philo)
{
	if (pthread_create(&philo[0].thread, NULL, routine_one_philo,
			&philo[0]) != 0)
	{
		printf("Failed to join thread for philo 1\n");
		return ;
	}
	if (pthread_join(philo[0].thread, NULL))
	{
		printf("Failed to join thread for philo 1\n");
		return ;
	}
}

void	one_philo(t_rules *arg)
{
	if (arg->nb_philo == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(arg->t_die * 1000);
		printf("%d  1  is died", arg->t_die);
		free(arg->forks);
		free(arg->philo);
		free(arg);
		exit(1);
	}
}
