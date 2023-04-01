/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiez-ga <sdiez-ga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:09:39 by sdiez-ga          #+#    #+#             */
/*   Updated: 2023/04/01 19:24:21 by sdiez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	assign_mutexes(t_gldata *gld)
{
	int			i;
	t_philo		*p;
	t_philodata	*pd;

	i = 0;
	pd = gld->philodata;
	while (i < pd->philo_count)
	{
		p = gld->philo_arr[i];
		p->state_mutex = gld->state_mutex_arr + i;
		p->lte_mutex = gld->lte_mutex_arr + i;
		p->left_fork = get_fork(i, gld->fork_arr, pd->philo_count);
		p->right_fork = get_fork(i + 1, gld->fork_arr, pd->philo_count);
		i++;
	}
}

t_ph_monitor	*init_ph_monitor(t_gldata *gld)
{
	t_ph_monitor	*pm;

	pm = malloc(sizeof(t_ph_monitor));
	if (!pm)
		return (0);
	pm->void_gld = gld;
	pm->thread_id = 0;
	return (pm);
}
