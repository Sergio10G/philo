/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiez-ga <sdiez-ga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:10:59 by sdiez-ga          #+#    #+#             */
/*   Updated: 2022/11/10 14:24:15 by sdiez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	*thread_routine(void *arg)
{
	t_philo	*philo;
	philo = (t_philo*)arg;

	while (1)
	{
		philo_action(philo->index, "is thinking", C_GREEN, philo->start_time);
		pthread_mutex_lock(philo->fork_arr);
		philo->last_time_eaten = philo_action(philo->index, "has taken a fork", C_YELLOW, philo->start_time);
		philo_action(philo->index, "is eating", C_YELLOW, philo->start_time);
		sleep_ms(philo->philodata->tm_eat);
		pthread_mutex_unlock(philo->fork_arr);
		philo_action(philo->index, "is sleeping", C_BLUE, philo->start_time);
		sleep_ms(philo->philodata->tm_sleep);
	}
	philo_action(philo->index, "died", C_RED, philo->start_time);
	return 0;
}

long int	philo_action(int philo_ind, char *action_msg, char *color, long int st)
{
	struct timeval	tv;
	long int		time;

	gettimeofday(&tv, 0);
	time = get_time_ms(tv) - st;
	printf("%s%ld\t%d %s%s\n", color, time, philo_ind + 1, action_msg, C_RESET);
	return (time);
}
