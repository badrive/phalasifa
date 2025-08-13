/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaras <bfaras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 11:09:10 by bfaras            #+#    #+#             */
/*   Updated: 2025/08/13 11:26:16 by bfaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parsing(char **av, int ac, t_rules *arg)
{
	int (i), (j);
	i = 1;
	j = 0;
	if (ac - 1 > 5 || ac - 1 < 4)
		write_err(arg);
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] == '+')
				j++;
			if (ft_isdigit(av[i][j]) == 0)
				write_err(arg);
			j++;
		}
		i++;
	}
	arg->nb_philo = ft_atoi(av[1], arg, 0);
	arg->t_die = ft_atoi(av[2], arg, 0);
	arg->t_eat = ft_atoi(av[3], arg, 0);
	arg->t_sleep = ft_atoi(av[4], arg, 0);
	if (--ac == 5)
		arg->must_eat = ft_atoi(av[5], arg, 0);
}

void	init_all(t_rules *arg)
{
	int	i;

	i = 0;
	arg->forks = malloc(sizeof(pthread_mutex_t) * (arg->nb_philo));
	arg->philo = malloc(sizeof(t_philo) * (arg->nb_philo));
	if (!arg->forks || !arg->philo)
		return ;
	while (i < arg->nb_philo)
	{
		if (pthread_mutex_init(&arg->forks[i], NULL) != 0)
			return ;
		i++;
	}
	pthread_mutex_init(&arg->write_lock, NULL);
	pthread_mutex_init(&arg->meal_lock, NULL);
	pthread_mutex_init(&arg->stop_lock, NULL);
	loop_init(arg, arg->philo);
	arg->finished_count = 0;
}

void	loop_init(t_rules *arg, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < arg->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].meals_eaten = 0;
		philo[i].last_meal = get_time_ms();
		philo[i].left_fork = &arg->forks[i];
		philo[i].right_fork = &arg->forks[(i + 1) % arg->nb_philo];
		philo[i].arg = arg;
		if (arg->nb_philo > 1)
			philo[i].loop = 1;
		else
			philo[i].loop = 0;
		i++;
	}
	arg->philo = philo;
}
