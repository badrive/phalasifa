/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaras <bfaras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 09:39:05 by bfaras            #+#    #+#             */
/*   Updated: 2025/08/13 11:26:43 by bfaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_err(t_rules *philo)
{
	write(2, "ERROR\n", 6);
	free(philo);
	exit(1);
}

int	check_loob(t_philo *philo)
{
	int	j;

	pthread_mutex_lock(&philo->arg->stop_lock);
	j = philo->loop;
	pthread_mutex_unlock(&philo->arg->stop_lock);
	return (j);
}

long	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	print_message(t_philo *philo, char *str)
{
	if (check_loob(philo))
	{
		pthread_mutex_lock(&philo->arg->write_lock);
		ft_putnbr_fd(get_time_ms() - philo->start_time, 1);
		write(1, " ", 1);
		ft_putnbr_fd(philo->id, 1);
		write(1, " ", 1);
		ft_putstr_fd(str, 1);
		ft_putchar_fd('\n', 1);
		pthread_mutex_unlock(&philo->arg->write_lock);
	}
}

void	print_isdied(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->arg->write_lock);
	ft_putnbr_fd(get_time_ms() - philo->start_time, 1);
	write(1, " ", 1);
	ft_putnbr_fd(philo->id, 1);
	write(1, " ", 1);
	ft_putstr_fd(str, 1);
	ft_putchar_fd('\n', 1);
	pthread_mutex_unlock(&philo->arg->write_lock);
}
