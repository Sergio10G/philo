/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiez-ga <sdiez-ga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:10:59 by sdiez-ga          #+#    #+#             */
/*   Updated: 2023/03/21 19:28:09 by sdiez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

long int	philo_action(t_philo *p, char *action_msg, char *color)
{
	long int	t;

	t = get_time_ms() - p->start_time;
	pthread_mutex_lock(p->philodata->simul_mutex);
	if (p->philodata->simul_active)
	{
		ft_putstr(color);
		ft_putlong(t);
		write(1, "\t", 1);
		ft_putlong(p->index + 1);
		write(1, " ", 1);
		ft_putstr(action_msg);
		ft_putstr(C_RESET);
		write(1, "\n", 1);
	}
	pthread_mutex_unlock(p->philodata->simul_mutex);
	return (t);
}

void	*thread_routine(void *arg)
{
	t_philo		*p;

	p = (t_philo *)arg;
	while (simul_and_philo_alive(p))
	{
		philo_action(p, "is thinking", C_GREEN);
		if (!simul_and_philo_alive(p))
			break ;
		if (!eat_routine(p))
			break ;
		p->times_eaten += 1;
		if (p->times_eaten == p->philodata->eat_times_count)
			break ;
		if (!simul_and_philo_alive(p))
			break ;
		if (!sleep_routine(p))
			break ;
	}
	pthread_mutex_lock(p->state_mutex);
	if (p->state && p->philodata->eat_times_count != -1)
		p->state = 2;
	pthread_mutex_unlock(p->state_mutex);
	return (0);
}

int	eat_routine(t_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	philo_action(p, "has taken a fork", C_CYAN);
	if (!p->right_fork)
	{
		sleep_ms(p->philodata->tm_die);
		pthread_mutex_lock(p->state_mutex);
		p->state = 0;
		pthread_mutex_unlock(p->state_mutex);
		pthread_mutex_unlock(p->left_fork);
		return (0);
	}
	if (!simul_and_philo_alive(p))
	{
		pthread_mutex_unlock(p->left_fork);
		return (0);
	}
	pthread_mutex_lock(p->right_fork);
	philo_action(p, "has taken a fork", C_CYAN);
	pthread_mutex_lock(p->lte_mutex);
	p->lte = philo_action(p, "is eating", C_BLUE);
	//ft_putstr("after\n");
	pthread_mutex_unlock(p->lte_mutex);
	die_during_action(p, p->lte, p->philodata->tm_eat);
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
	return (eat_return(p));
}

int	sleep_routine(t_philo *p)
{
	long int	now;

	now = philo_action(p, "is sleeping", C_PURPLE);
	return (die_during_action(p, now, p->philodata->tm_sleep));
}

int	die_during_action(t_philo *p, long int now, int action_time)
{
	long int	lte;

	pthread_mutex_lock(p->lte_mutex);
	lte = p->lte;
	pthread_mutex_unlock(p->lte_mutex);
	if (now + action_time > lte + p->philodata->tm_die)
	{
		sleep_ms((lte + p->philodata->tm_die) - now);
		pthread_mutex_lock(p->state_mutex);
		p->state = 0;
		pthread_mutex_unlock(p->state_mutex);
		return (0);
	}
	sleep_ms(action_time);
	return (1);
}
