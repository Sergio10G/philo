/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiez-ga <sdiez-ga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:10:47 by sdiez-ga          #+#    #+#             */
/*   Updated: 2023/04/06 18:38:09 by sdiez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	free_gldata(t_gldata *gld)
{
	if (gld->philo_arr)
		free_philo_array(gld);
	if (gld->ph_monitor_arr)
		free_monitor_array(gld);
	if (gld->fork_arr || gld->state_mutex_arr || gld->lte_mutex_arr)
		free_mutex_arrays(gld);
	if (gld->philodata)
		free_philodata(gld->philodata);
	if (gld->monitor_mutex)
	{
		pthread_mutex_destroy(gld->monitor_mutex);
		free(gld->monitor_mutex);
	}
	free(gld);
}

void	free_philo_array(t_gldata *gld)
{
	int	i;

	i = 0;
	while (i < gld->philodata->philo_count)
	{
		if (gld->philo_arr[i])
			free(gld->philo_arr[i]);
		gld->philo_arr[i] = 0;
		i++;
	}
	free(gld->philo_arr);
	gld->philo_arr = 0;
}

void	free_monitor_array(t_gldata *gld)
{
	int	i;

	i = 0;
	while (i * PHILOS_PER_MONITOR < gld->philodata->philo_count)
	{
		if (gld->ph_monitor_arr[i])
			free(gld->ph_monitor_arr[i]);
		gld->ph_monitor_arr[i] = 0;
		i++;
	}
	free(gld->ph_monitor_arr);
	gld->ph_monitor_arr = 0;
}

void	free_mutex_arrays(t_gldata *gld)
{
	int	i;

	i = 0;
	while (i < gld->philodata->philo_count)
	{
		if (gld->fork_arr && gld->fork_arr + i)
			pthread_mutex_destroy(gld->fork_arr + i);
		if (gld->state_mutex_arr && gld->state_mutex_arr + i)
			pthread_mutex_destroy(gld->state_mutex_arr + i);
		if (gld->lte_mutex_arr && gld->lte_mutex_arr + i)
			pthread_mutex_destroy(gld->lte_mutex_arr + i);
		i++;
	}
	if (gld->fork_arr)
		free(gld->fork_arr);
	gld->fork_arr = 0;
	if (gld->state_mutex_arr)
		free(gld->state_mutex_arr);
	gld->state_mutex_arr = 0;
	if (gld->lte_mutex_arr)
		free(gld->lte_mutex_arr);
	gld->lte_mutex_arr = 0;
}

void	free_philodata(t_philodata *pd)
{
	if (!pd)
		return ;
	if (pd->simul_mutex)
	{
		pthread_mutex_destroy(pd->simul_mutex);
		free(pd->simul_mutex);
	}
	pd->simul_mutex = 0;
	if (pd->print_mutex)
	{
		pthread_mutex_destroy(pd->print_mutex);
		free(pd->print_mutex);
	}
	pd->print_mutex = 0;
	if (pd)
		free(pd);
}
