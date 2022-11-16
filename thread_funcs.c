/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiez-ga <sdiez-ga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:10:59 by sdiez-ga          #+#    #+#             */
/*   Updated: 2022/11/16 16:26:45 by sdiez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

long int	philo_action(int ind, char *action_msg, char *color, long int st)
{
	long int	time;

	time = get_time_ms() - st;
	printf("%s%ld\t%d %s%s\n", color, time, ind + 1, action_msg, C_RESET);
	return (time);
}

void	*thread_routine(void *arg)
{
	int		eat_return;
	t_philo	*philo;

	philo = (t_philo*)arg;
	while (philo->philodata->simul_active)
	{
		philo_action(philo->index, "is thinking", C_GREEN, philo->start_time);
		if (!philo->philodata->simul_active)
			break ;
		eat_return = eat_routine(philo);
		if (!eat_return || !philo->philodata->simul_active)
			break ;
		if (philo->times_eaten == philo->philodata->eat_times_count)
			break;
		philo_action(philo->index, "is sleeping", C_PURPLE, philo->start_time);
		sleep_ms(philo->philodata->tm_sleep);
	}
	if (!philo->state)
		philo_action(philo->index, "died", C_RED, philo->start_time);
	philo->state = 0;
	return 0;
}

int	eat_routine(t_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	philo_action(p->index, "has taken a fork", C_CYAN, p->start_time);
	if (p->philodata->philo_count == 1)
		sleep_ms(p->philodata->tm_die + 1);
	if (!p->philodata->simul_active)
	{
		pthread_mutex_unlock(p->left_fork);
		return (0);
	}
	pthread_mutex_lock(p->right_fork);
	p->lte = philo_action(p->index, "has taken a fork", C_CYAN, p->start_time);
	philo_action(p->index, "is eating", C_BLUE, p->start_time);
	sleep_ms(p->philodata->tm_eat);
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
	p->times_eaten++;
	return (1);
}
