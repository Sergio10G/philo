/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiez-ga <sdiez-ga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:19:28 by sdiez-ga          #+#    #+#             */
/*   Updated: 2022/11/16 17:01:10 by sdiez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	sleep_ms(int ms)
{
	long int	desired_time_us;

	desired_time_us = (get_time_ms() + ms) * 1000;
	//while (get_time_ms() * 1000 <= desired_time_us - ms)
	while (get_time_ms() * 1000 < desired_time_us)
		usleep(ms);
	/*
	desired_time_us -= get_time_ms() * 1000;
	if (desired_time_us > 0)
		usleep(desired_time_us);
	*/
}

long int	get_time_ms()
{
	struct timeval	tv;

	gettimeofday(&tv, 0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

pthread_mutex_t	*get_fork(int i, pthread_mutex_t *fork_arr, int arr_size)
{
	if (i >= arr_size)
		i = 0;
	return (fork_arr + i);
}
