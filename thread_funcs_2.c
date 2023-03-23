/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_funcs_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiez-ga <sdiez-ga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:51:01 by sdiez-ga          #+#    #+#             */
/*   Updated: 2023/03/23 14:13:23 by sdiez-ga         ###   ########.fr       */
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

	pm = (t_ph_monitor *)arg;
	p = pm->philo;
	pthread_create(&(p->thread_id), 0, &thread_routine, p);
	while (is_simul_active(p->philodata))
	{
		if (check_death_main(p))
		{
			pthread_mutex_lock(p->state_mutex);
			p->state = 0;
			pthread_mutex_unlock(p->state_mutex);
			announce_death(p);
			break ;
		}
		sleep_ms(1);
	}
	pthread_join(p->thread_id, 0);
	return (0);
}
