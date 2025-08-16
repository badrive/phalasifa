/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaras <bfaras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 09:46:32 by bfaras            #+#    #+#             */
/*   Updated: 2025/08/16 20:54:52 by bfaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_join(t_rules *arg)
{
	int	i;

	i = 0;
	while (i < arg->nb_philo)
	{
		pthread_join(arg->philo[i].thread, NULL);
		i++;
	}
}

int	philo_is_died(t_philo *philo, int i)
{
	int		j;
	long	time;

	j = 0;
	pthread_mutex_lock(&philo->arg->meal_lock);
	time = get_time_ms() - philo[i].last_meal;
	pthread_mutex_unlock(&philo->arg->meal_lock);
	if (time > philo->arg->t_die)
	{
		pthread_mutex_lock(&philo->arg->stop_lock);
		j = 0;
		while (j < philo->arg->nb_philo)
		{
			philo[j].loop = 0;
			j++;
		}
		print_isdied(&philo[i], "is died");
		pthread_mutex_unlock(&philo->arg->stop_lock);
		return (1);
	}
	return (0);
}

int	philo_must_eat(t_philo *philo, int i)
{
	if (philo[i].arg->must_eat)
	{
		pthread_mutex_lock(&philo->arg->meal_lock);
		if (philo[i].meals_eaten >= philo->arg->must_eat && philo[i].loop != 0)
		{
			pthread_mutex_lock(&philo->arg->write_lock);
			pthread_mutex_lock(&philo->arg->stop_lock);
			philo[i].loop = 0;
			pthread_mutex_unlock(&philo->arg->stop_lock);
			philo->arg->finished_count++;
			if (philo->arg->finished_count >= philo->arg->nb_philo
				&& philo[i].id % 2 != 0)
			{
				pthread_mutex_unlock(&philo->arg->write_lock);
				pthread_mutex_unlock(&philo->arg->meal_lock);
				return (1);
			}
			pthread_mutex_unlock(&philo->arg->write_lock);
		}
		pthread_mutex_unlock(&philo->arg->meal_lock);
	}
	return (0);
}

void	create_thread(t_rules *arg)
{
	int	i;

	i = 0;
	while (i < arg->nb_philo)
	{
		arg->philo[i].start_time = get_time_ms();
		if ((pthread_create(&arg->philo[i].thread, NULL, routine,
					&arg->philo[i])) != 0)
		{
			perror("Failed to create thread for philo");
			return ;
		}
		i++;
	}
}

void	monitor(t_philo *philo)
{
	int	i;

	i = 0;
	while (1)
	{
		if (philo_is_died(philo, i) == 1)
			break ;
		if (philo_must_eat(philo, i) == 1)
			break ;
		i++;
		if (i >= philo->arg->nb_philo)
			i = 0;
		usleep(500);
	}
}