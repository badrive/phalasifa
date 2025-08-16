/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaras <bfaras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 11:09:46 by bfaras            #+#    #+#             */
/*   Updated: 2025/08/16 20:55:22 by bfaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy(t_rules *arg)
{
	int	i;

	if (!arg)
		return ;
	if (arg->forks)
	{
		i = 0;
		while (i < arg->nb_philo)
		{
			pthread_mutex_destroy(&arg->forks[i]);
			i++;
		}
		free(arg->forks);
		arg->forks = NULL;
	}
	pthread_mutex_destroy(&arg->write_lock);
	pthread_mutex_destroy(&arg->meal_lock);
	pthread_mutex_destroy(&arg->stop_lock);
	if (arg->philo)
	{
		free(arg->philo);
		arg->philo = NULL;
	}
	free(arg);
}

int	main(int ac, char **av)
{
	t_rules	*arg;

	arg = malloc(sizeof(t_rules));
	parsing(av, ac, arg);
	init_all(arg);
	if (arg->nb_philo == 1)
	{
		one_philo_t(arg->philo);
		ft_destroy(arg);
		exit(1);
	}
	else
	{
		create_thread(arg);
		monitor(arg->philo);
		ft_join(arg);
		ft_destroy(arg);
	}
}
