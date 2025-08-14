/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaras <bfaras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 09:38:35 by bfaras            #+#    #+#             */
/*   Updated: 2025/08/14 20:57:29 by bfaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str, t_rules *philo, long nb)
{
	int (i), (j);
	if (!str)
		return (0);
	i = 0;
	j = 1;
	nb = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		j *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + (str[i] - 48);
		if (nb < 0 || nb > 2147483647)
			write_err(philo);
		i++;
	}
	if (nb == 0)
		write_err(philo);
	return ((int)(nb * j));
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, s + i, 1);
		i++;
	}
	write(fd, " ", 1);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(long n, int fd)
{
	{
		if (n == -2147483648)
		{
			ft_putnbr_fd(n / 10, fd);
			ft_putchar_fd('8', fd);
		}
		else if (n < 0)
		{
			ft_putchar_fd('-', fd);
			ft_putnbr_fd(-n, fd);
		}
		else if (n > 9)
		{
			ft_putnbr_fd(n / 10, fd);
			ft_putnbr_fd(n % 10, fd);
		}
		else if (n <= 9)
		{
			ft_putchar_fd((n + '0'), fd);
		}
	}
}

int	ft_isdigit(int c)
{
	if ((c >= 48 && c <= 57) || c == 32)
		return (1);
	return (0);
}
