/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiez-ga <sdiez-ga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:19:28 by sdiez-ga          #+#    #+#             */
/*   Updated: 2022/11/11 14:26:02 by sdiez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	sleep_ms(int ms)
{
	usleep(ms * 1000);
}

long int	get_time_ms()
{
	struct timeval	tv;

	gettimeofday(&(tv), 0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

pthread_mutex_t	*get_fork(int i, pthread_mutex_t *fork_arr, int arr_size)
{
	if (i >= arr_size)
		i = 0;
	return (fork_arr + i);
}
