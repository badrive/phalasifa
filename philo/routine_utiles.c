/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utiles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaras <bfaras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 09:36:34 by bfaras            #+#    #+#             */
/*   Updated: 2025/08/14 20:19:24 by bfaras           ###   ########.fr       */
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
	pthread_mutex_lock(&philo->arg->write_lock);
	printf("0 %d has taken a fork\n", philo->id);
	pthread_mutex_unlock(&philo->arg->write_lock);
	ft_usleep(philo->arg->t_die, philo);
	pthread_mutex_lock(&philo->arg->write_lock);
	printf("%d %d died\n", philo->arg->t_die, philo->id);
	pthread_mutex_unlock(&philo->arg->write_lock);
	return (NULL);
}

void	one_philo_t(t_philo *philo)
{
	if (pthread_create(&philo[0].thread, NULL, routine_one_philo,
			&philo[0]) != 0)
	{
		printf("Failed to create thread for philosopher %d\n", philo[0].id);
		return ;
	}
	if (pthread_join(philo[0].thread, NULL) != 0)
	{
		printf("Failed to join thread for philosopher %d\n", philo[0].id);
		return ;
	}
}
