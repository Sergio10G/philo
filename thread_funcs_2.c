/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_funcs_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiez-ga <sdiez-ga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:51:01 by sdiez-ga          #+#    #+#             */
/*   Updated: 2023/04/19 18:21:11 by sdiez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	sleep_routine(t_philo *p)
{
	long int	now;

	now = philo_action(p, "is sleeping", C_PURPLE);
	return (die_during_action(p, now, p->philodata->tm_sleep));
}

void	*monitor_routine(void *arg)
{
	t_ph_monitor	*pm;
	t_gldata		*gld;
	int				offset;
	int				i;
	int				philo_count;

	pm = (t_ph_monitor *) arg;
	gld = (t_gldata *) pm->void_gld;
	pthread_mutex_lock(gld->monitor_mutex);
	offset = pm->index * PHILOS_PER_MONITOR;
	philo_count = gld->philodata->philo_count - offset;
	if (philo_count > PHILOS_PER_MONITOR)
		philo_count = PHILOS_PER_MONITOR;
	i = 0;
	while (i < philo_count)
	{
		pthread_create(&(gld->philo_arr[offset + i]->thread_id), 0, \
						&thread_routine, gld->philo_arr[offset + i]);
		usleep(100);
		i++;
	}
	pthread_mutex_unlock(gld->monitor_mutex);
	monitor_loop(gld, philo_count, offset);
	monitor_join(gld, philo_count, offset);
	return (0);
}

void	monitor_loop(t_gldata *gld, int pc, int off)
{
	t_philo	*p;
	int		i;

	i = 0;
	while (1)
	{
		p = gld->philo_arr[off + i];
		if (check_death_main(p))
		{
			pthread_mutex_lock(p->philodata->print_mutex);
			announce_death(p);
			p->philodata->printable = 0;
			pthread_mutex_unlock(p->philodata->print_mutex);
			pthread_mutex_lock(p->state_mutex);
			p->state = 0;
			pthread_mutex_unlock(p->state_mutex);
			break ;
		}
		if (!is_simul_active(gld->philodata))
			break ;
		i++;
		if (i >= pc)
			i = 0;
		usleep(100);
	}
}

void	monitor_join(t_gldata *gld, int pc, int off)
{
	int		i;
	t_philo	*p;

	i = 0;
	while (i < pc)
	{
		p = gld->philo_arr[off + i];
		pthread_join(p->thread_id, 0);
		i++;
	}
}
