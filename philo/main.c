/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaras <bfaras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 11:09:46 by bfaras            #+#    #+#             */
/*   Updated: 2025/08/12 15:18:35 by bfaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_rules	*arg;

	arg = malloc(sizeof(t_rules));
	parsing(av, ac, arg);
	init_all(arg);
	if (arg->nb_philo == 1)
	{
		one_philo(arg);
		one_philo_t(arg->philo);
	}
	else
	{
		create_thread(arg);
		monitor(arg->philo);
		joun(arg);
	}
}
