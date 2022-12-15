/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiez-ga <sdiez-ga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:19:28 by sdiez-ga          #+#    #+#             */
/*   Updated: 2022/12/15 19:06:11 by sdiez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	sleep_ms(int ms)
{
	long int	desired_time_us;

	desired_time_us = (get_time_ms() + ms) * 1000;
	while (get_time_ms() * 1000 < desired_time_us)
		usleep(ms);
}

long int	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, 0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	is_simul_active(t_philodata *pd)
{
	int	status;

	pthread_mutex_lock(pd->simul_mutex);
	status = pd->simul_active;
	pthread_mutex_unlock(pd->simul_mutex);
	return (status);
}

int	simul_and_philo_alive(t_philo *p)
{
	int	status;

	pthread_mutex_lock(p->state_mutex);
	status = (p->state && is_simul_active(p->philodata));
	pthread_mutex_unlock(p->state_mutex);
	return (status);
}

int	check_death_main(t_philo *p)
{
	int	result;

	pthread_mutex_lock(p->state_mutex);
	result = ((get_time_ms() - p->start_time - p->lte > p->philodata->tm_die \
			|| p->state == 0) && p->state != 2);
	pthread_mutex_unlock(p->state_mutex);
	return (result);
}
