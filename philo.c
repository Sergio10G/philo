/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiez-ga <sdiez-ga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:51:33 by sdiez-ga          #+#    #+#             */
/*   Updated: 2022/11/16 17:13:53 by sdiez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	main(int argc, char **argv)
{
	t_philodata	*pd;
	t_gldata	*gld;

	pd = 0;
	gld = 0;
	if (!alloc_phase(argc, argv, &pd, &gld))
		return (1);
	simulation_phase(gld);
	free_gldata(gld);
}

int	alloc_phase(int argc, char **argv, t_philodata **pd, t_gldata **gld)
{
	int			error_comp;

	*pd = init_philodata();
	if (!*pd)
		return (0);
	if (!parse_input(argc, argv, *pd))
		return (0);
	*gld = init_gldata(*pd);
	if (!*gld)
	{
		free(*pd);
		return (0);
	}
	error_comp = populate_fork_array(*gld);
	error_comp += populate_philo_array(*gld);
	if (error_comp != 2)
	{
		free_gldata(*gld);
		return (0);
	}
	return (1);
}

void	simulation_phase(t_gldata *gld)
{
	long int	time;
	int			i;

	time = get_time_ms();
	i = -1;
	while (++i < gld->philodata->philo_count)
	{
		gld->philo_arr[i]->start_time = time;
		pthread_create(&(gld->philo_arr[i]->thread_id), 0, &thread_routine, gld->philo_arr[i]);
		sleep_ms(1);
	}
	while (gld->philodata->simul_active)
	{
		i = 0;
		while (i < gld->philodata->philo_count)
		{
			t_philo *philo = gld->philo_arr[i];
			if (get_time_ms() - philo->start_time - philo->lte > gld->philodata->tm_die)
			{
				philo->state = 0;
				gld->philodata->simul_active = 0;
				pthread_join(philo->thread_id, 0);
				break ;
			}
		}
	}
}

void	free_gldata(t_gldata *gldata)
{
	int	i;

	if (gldata->philo_arr)
	{
		i = 0;
		while (i < gldata->philodata->philo_count)
		{
			free(gldata->philo_arr[i]);
			i++;
		}
		free(gldata->philo_arr);
	}
	if (gldata->fork_arr)
	{
		i = 0;
		while (i < gldata->philodata->philo_count)
		{
			pthread_mutex_destroy(gldata->fork_arr + i);
			i++;
		}
		free(gldata->fork_arr);
	}
	if (gldata->philodata)
		free(gldata->philodata);
	free(gldata);
}
