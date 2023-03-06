/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiez-ga <sdiez-ga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:56:38 by sdiez-ga          #+#    #+#             */
/*   Updated: 2023/03/06 16:02:51 by sdiez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

t_philo	*init_philo(t_philodata *pd, pthread_mutex_t *fork_arr, int index)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (0);
	memset(philo, 0, sizeof(t_philo));
	philo->state = 1;
	philo->philodata = pd;
	philo->index = index;
	philo->left_fork = get_fork(index, fork_arr, pd->philo_count);
	philo->right_fork = get_fork(index + 1, fork_arr, pd->philo_count);
	return (philo);
}

t_philodata	*init_philodata(void)
{
	t_philodata	*pd;

	pd = malloc(sizeof(t_philodata));
	if (!pd)
		return (0);
	memset(pd, 0, sizeof(t_philodata));
	pd->simul_mutex = malloc(sizeof(pthread_mutex_t));
	if (!pd->simul_mutex)
		return (0);
	if (pthread_mutex_init(pd->simul_mutex, 0))
	{
		free(pd->simul_mutex);
		return (0);
	}
	return (pd);
}

t_gldata	*init_gldata(t_philodata *pd)
{
	t_gldata	*gld;

	gld = malloc(sizeof(t_gldata));
	if (!gld)
		return (0);
	gld->philodata = pd;
	gld->philo_arr = malloc(pd->philo_count * sizeof(t_philo *));
	gld->fork_arr = malloc(pd->philo_count * sizeof(pthread_mutex_t));
	gld->state_mutex_arr = malloc(pd->philo_count * sizeof(pthread_mutex_t));
	gld->lte_mutex_arr = malloc(pd->philo_count * sizeof(pthread_mutex_t));
	if (!gld->philo_arr || !gld->fork_arr || !gld->state_mutex_arr || \
		!gld->lte_mutex_arr)
	{
		free_gldata(gld);
		return (0);
	}
	return (gld);
}

int	populate_mutex_arrays(t_gldata *gld)
{
	int	i;
	int	mutex_error;

	i = 0;
	while (i < gld->philodata->philo_count)
	{
		mutex_error = pthread_mutex_init(gld->fork_arr + i, 0);
		mutex_error += pthread_mutex_init(gld->state_mutex_arr + i, 0);
		mutex_error += pthread_mutex_init(gld->lte_mutex_arr + i, 0);
		if (mutex_error)
		{
			free_mutex_arrays(gld);
			return (0);
		}
		i++;
	}
	return (1);
}

int	populate_philo_array(t_gldata *gld)
{
	int	i;

	i = 0;
	while (i < gld->philodata->philo_count)
	{
		gld->philo_arr[i] = init_philo(gld->philodata, gld->fork_arr, i);
		if (!gld->philo_arr[i])
		{
			while (--i >= 0)
				free(gld->philo_arr[i]);
			free(gld->philo_arr);
			gld->philo_arr = 0;
			return (0);
		}
		i++;
	}
	return (1);
}
