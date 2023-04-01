/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiez-ga <sdiez-ga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 17:22:22 by sdiez-ga          #+#    #+#             */
/*   Updated: 2023/04/01 19:32:47 by sdiez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

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
	int			result;
	long int	lte;

	pthread_mutex_lock(p->lte_mutex);
	lte = p->lte;
	pthread_mutex_unlock(p->lte_mutex);
	pthread_mutex_lock(p->state_mutex);
	result = ((get_time_ms() - p->philodata->start_time - lte > p->philodata->tm_die \
			|| p->state == 0) && p->state != 2);
	pthread_mutex_unlock(p->state_mutex);
	return (result);
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
