/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_funcs_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiez-ga <sdiez-ga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:51:01 by sdiez-ga          #+#    #+#             */
/*   Updated: 2023/04/01 19:46:14 by sdiez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	eat_return(t_philo *p)
{
	int	ret_val;

	pthread_mutex_lock(p->state_mutex);
	ret_val = p->state;
	pthread_mutex_unlock(p->state_mutex);
	return (ret_val);
}

void	*monitor_routine(void *arg)
{
	t_philo			*p;
	t_ph_monitor	*pm;
	t_gldata		*gld;
	int				offset;
	int				i;
	int				philo_count;

	pm = (t_ph_monitor *) arg;
	gld = (t_gldata *) pm->void_gld;
	pthread_mutex_lock(gld->monitor_mutex);
	// ASDASD
	//ft_putlong(pm->index);
	//ft_putstr(" STARTED ---------------------------------------------------\n");
	// ASDASD
	offset = pm->index * PHILOS_PER_MONITOR;
	philo_count = gld->philodata->philo_count - offset;
	if (philo_count > PHILOS_PER_MONITOR)
		philo_count = PHILOS_PER_MONITOR;
	i = 0;
	while (i < philo_count)
	{
		p = gld->philo_arr[offset + i];
		pthread_create(&(p->thread_id), 0, &thread_routine, p);
		usleep(100);
		i++;
	}
	pthread_mutex_unlock(gld->monitor_mutex);
	i = 0;
	while (1)
	{
		p = gld->philo_arr[offset + i];
		if (check_death_main(p))
		{
			pthread_mutex_lock(p->state_mutex);
			p->state = 0;
			pthread_mutex_unlock(p->state_mutex);
			announce_death(p);
			break ;
		}
		//sleep_ms(1);
		if (!is_simul_active(gld->philodata))
			break;
		i++;
		if (i >= philo_count)
			i = 0;
	}
	i = 0;
	while (i < philo_count)
	{
		p = gld->philo_arr[offset + i];
		pthread_join(p->thread_id, 0);
		i++;
	}
	return (0);
}
