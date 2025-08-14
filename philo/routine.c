/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaras <bfaras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 09:34:09 by bfaras            #+#    #+#             */
/*   Updated: 2025/08/14 20:55:30 by bfaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_message(philo, "has taken a fork");
	}
	else
	{
		usleep(300);
		pthread_mutex_lock(philo->right_fork);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, "has taken a fork");
	}
}

void	eating(t_philo *philo)
{
	take_forks(philo);
	print_message(philo, "is eating");
	ft_usleep(philo->arg->t_eat, philo);
	pthread_mutex_lock(&philo->arg->meal_lock);
	philo->last_meal = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->arg->meal_lock);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleeping(t_philo *philo)
{
	print_message(philo, "is sleeping");
	ft_usleep(philo->arg->t_sleep, philo);
}

void	thinking(t_philo *philo)
{
	print_message(philo, "is thinking");
}

void	ft_usleep(int time, t_philo *philo)
{
	long	time_star;
	int		time_courr;

	time_star = get_time_ms();
	time_courr = get_time_ms() - time_star;
	while (time_courr < time)
	{
		pthread_mutex_lock(&philo->arg->stop_lock);
		if (philo->loop == 0)
		{
			pthread_mutex_unlock(&philo->arg->stop_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->arg->stop_lock);
		usleep(100);
		time_courr = get_time_ms() - time_star;
	}
}
