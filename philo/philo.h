/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaras <bfaras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 11:10:20 by bfaras            #+#    #+#             */
/*   Updated: 2025/08/13 11:26:08 by bfaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal;
	long			start_time;
	int				loop;
	struct s_rules	*arg;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_philo;

typedef struct s_rules
{
	int				nb_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				must_eat;
	int				finished_count;
	t_philo			*philo;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	stop_lock;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
}					t_rules;

//parsing of  my programme

void				parsing(char **av, int ac, t_rules *arg);
void				write_err(t_rules *philo);
int					check_loob(t_philo *philo);
void				print_message(t_philo *philo, char *str);
void				print_isdied(t_philo *philo, char *str);

//utiles  of  my programme

int					ft_atoi(const char *str, t_rules *philo, long nb);
int					ft_isdigit(int c);
void				ft_putnbr_fd(long n, int fd);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);

//init_all

void				init_all(t_rules *arg);
void				loop_init(t_rules *arg, t_philo *philo);

//my_ programme

long				get_time_ms(void);
void				joun(t_rules *arg);
void				ft_usleep(int time, t_philo *philo);
void				create_thread(t_rules *arg);
void				one_philo_t(t_philo *philo);
void				one_philo(t_rules *arg);
void				monitor(t_philo *philo);
void				create_thread(t_rules *arg);
int					philo_must_eat(t_philo *philo, int i);
int					philo_is_died(t_philo *philo, int i);

//routine of  my philo

void				eating(t_philo *philo);
void				sleeping(t_philo *philo);
void				thinking(t_philo *philo);
void				*routine_one_philo(void *arg);
void				*routine(void *arg);

#endif