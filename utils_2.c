/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiez-ga <sdiez-ga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:19:28 by sdiez-ga          #+#    #+#             */
/*   Updated: 2023/04/06 18:08:53 by sdiez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	sleep_ms(int ms)
{
	long int	desired_time_us;

	desired_time_us = (get_time_ms() + ms) * 1000;
	while (get_time_ms() * 1000 < desired_time_us)
		usleep(50);
}

long int	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, 0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_putstr(char *str)
{
	int	len;

	len = ft_strlen(str);
	write(1, str, len);
}

void	ft_putlong(long int n)
{
	unsigned long int	un;
	char				temp[21];
	int					i;

	if (n == 0)
	{
		write(1, "0", 1);
		return ;
	}
	i = 0;
	memset(temp, 0, 21);
	un = n;
	if (n < 0)
	{
		temp[i++] = '-';
		un = -n;
	}
	while (un > 0)
	{
		temp[i++] = (un % 10) + '0';
		un /= 10;
	}
	ft_putstr(rev_num(temp, i - 1));
}

char	*rev_num(char *temp, int last_pos)
{
	int		i;
	int		half;
	char	temp_char;

	i = 0;
	if (temp[0] == '-')
		i++;
	half = (last_pos + 1 - i) / 2;
	while (half > 0)
	{
		temp_char = temp[i];
		temp[i] = temp[last_pos];
		temp[last_pos] = temp_char;
		i++;
		last_pos--;
		half--;
	}
	return (temp);
}
