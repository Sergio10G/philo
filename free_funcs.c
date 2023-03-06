/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiez-ga <sdiez-ga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:10:47 by sdiez-ga          #+#    #+#             */
/*   Updated: 2023/03/06 16:10:18 by sdiez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	free_gldata(t_gldata *gld)
{
	if (gld->philo_arr)
		free_philo_array(gld);
	if (gld->fork_arr || gld->state_mutex_arr || gld->lte_mutex_arr)
		free_mutex_arrays(gld);
	if (gld->philodata)
		free_philodata(gld->philodata);
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
		i++;
	}
	free(gld->philo_arr);
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
	if (gld->state_mutex_arr)
		free(gld->state_mutex_arr);
	if (gld->lte_mutex_arr)
		free(gld->lte_mutex_arr);
}

void	free_philodata(t_philodata *pd)
{
	pthread_mutex_destroy(pd->simul_mutex);
	free(pd->simul_mutex);
	free(pd);
}
