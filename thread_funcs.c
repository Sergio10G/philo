/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiez-ga <sdiez-ga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:10:59 by sdiez-ga          #+#    #+#             */
/*   Updated: 2022/12/15 19:20:33 by sdiez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

long int	philo_action(t_philo *p, char *action_msg, char *color)
{
	long int	t;

	t = get_time_ms() - p->start_time;
	pthread_mutex_lock(p->philodata->simul_mutex);
	if (p->philodata->simul_active)
		printf("%s%ld\t%d %s%s\n", color, t, p->index + 1, action_msg, C_RESET);
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
	p->lte = philo_action(p, "is eating", C_BLUE);
	sleep_ms(p->philodata->tm_eat);
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
	return (1);
}

int	sleep_routine(t_philo *p)
{
	long int	now;

	now = philo_action(p, "is sleeping", C_PURPLE);
	if (now + p->philodata->tm_sleep > p->lte + p->philodata->tm_die)
	{
		sleep_ms((p->lte + p->philodata->tm_die) - now);
		pthread_mutex_lock(p->state_mutex);
		p->state = 0;
		pthread_mutex_unlock(p->state_mutex);
		return (0);
	}
	sleep_ms(p->philodata->tm_sleep);
	return (1);
}

void	finish_if_everyone_full(t_gldata *gld)
{
	t_philo		*p;
	t_philodata	*pd;
	int			i;
	int			full_philos;

	i = 0;
	full_philos = 0;
	pd = gld->philodata;
	while (i < pd->philo_count)
	{
		p = gld->philo_arr[i];
		pthread_mutex_lock(p->state_mutex);
		if (p->state == 2)
			full_philos++;
		pthread_mutex_unlock(p->state_mutex);
		i++;
	}
	if (full_philos == pd->philo_count)
	{
		pthread_mutex_lock(pd->simul_mutex);
		pd->simul_active = 0;
		pthread_mutex_unlock(pd->simul_mutex);
	}
}
