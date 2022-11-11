/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiez-ga <sdiez-ga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:10:59 by sdiez-ga          #+#    #+#             */
/*   Updated: 2022/11/11 14:43:36 by sdiez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	*thread_routine(void *arg)
{
	t_philo	*philo;
	philo = (t_philo*)arg;

	while (philo->philodata->simul_active)
	{
		philo_action(philo->index, "is thinking", C_GREEN, philo->start_time);
		if (!philo->philodata->simul_active)
			break ;
		pthread_mutex_lock(get_fork(philo->index, philo->fork_arr, philo->philodata->philo_count));
		philo->last_time_eaten = philo_action(philo->index, "has taken a fork", C_CYAN, philo->start_time);
		if (!philo->philodata->simul_active)
		{
			pthread_mutex_unlock(get_fork(philo->index, philo->fork_arr, philo->philodata->philo_count));
			break ;
		}
		pthread_mutex_lock(get_fork(philo->index + 1, philo->fork_arr, philo->philodata->philo_count));
		philo->last_time_eaten = philo_action(philo->index, "has taken a fork", C_CYAN, philo->start_time);
		philo_action(philo->index, "is eating", C_BLUE, philo->start_time);
		sleep_ms(philo->philodata->tm_eat);
		pthread_mutex_unlock(get_fork(philo->index, philo->fork_arr, philo->philodata->philo_count));
		pthread_mutex_unlock(get_fork(philo->index + 1, philo->fork_arr, philo->philodata->philo_count));
		if (!philo->philodata->simul_active)
			break ;
		philo_action(philo->index, "is sleeping", C_PURPLE, philo->start_time);
		sleep_ms(philo->philodata->tm_sleep);
	}
	if (!philo->state)
		philo_action(philo->index, "died", C_RED, philo->start_time);
	//philo_action(philo->index, "STOPPED", C_CYAN, philo->start_time);
	return 0;
}

long int	philo_action(int philo_ind, char *action_msg, char *color, long int st)
{
	long int		time;

	time = get_time_ms() - st;
	printf("%s%ld\t%d %s%s\n", color, time, philo_ind + 1, action_msg, C_RESET);
	return (time);
}
