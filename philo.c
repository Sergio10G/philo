/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiez-ga <sdiez-ga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:51:33 by sdiez-ga          #+#    #+#             */
/*   Updated: 2022/12/01 18:10:52 by sdiez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

/*
void leaks()
{
	system("leaks philo");
}
*/

int	main(int argc, char **argv)
{
	t_philodata	*pd;
	t_gldata	*gld;

	//atexit(leaks);
	pd = 0;
	gld = 0;
	if (!alloc_phase(argc, argv, &pd, &gld))
		return (1);
	launch_phase(gld);
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
	error_comp += populate_state_array(*gld);
	if (error_comp != 3)
	{
		free_gldata(*gld);
		return (0);
	}
	return (1);
}

void	launch_phase(t_gldata *gld)
{
	t_philo		*p;
	long int	time;
	int			i;

	time = get_time_ms();
	i = 0;
	while (i < gld->philodata->philo_count)
	{
		p = gld->philo_arr[i];
		p->start_time = time;
		p->state_mutex = gld->state_mutex_arr + i;
		pthread_create(&(p->thread_id), 0, &thread_routine, p);
		sleep_ms(1);
		i++;
	}
}

void	simulation_phase(t_gldata *gld)
{
	t_philo	*p;
	int		i;

	while (1)
	{
		i = -1;
		while (++i < gld->philodata->philo_count)
		{
			p = gld->philo_arr[i];
			pthread_mutex_lock(p->state_mutex);
			pthread_mutex_lock(p->philodata->simul_mutex);
			if (get_time_ms() - p->start_time - p->lte > gld->philodata->tm_die
				|| p->state == 0)
			{
				p->state = 0;
				gld->philodata->simul_active = 0;
				pthread_mutex_unlock(p->philodata->simul_mutex);
				pthread_mutex_unlock(p->state_mutex);
				break ;
			}
			pthread_mutex_unlock(p->philodata->simul_mutex);
			pthread_mutex_unlock(p->state_mutex);
		}
		pthread_mutex_lock(gld->philodata->simul_mutex);
		if (!gld->philodata->simul_active)
		{
			pthread_mutex_unlock(gld->philodata->simul_mutex);
			break ;
		}
		pthread_mutex_unlock(gld->philodata->simul_mutex);
	}
	i = -1;
	while (++i < gld->philodata->philo_count)
		pthread_join(gld->philo_arr[i]->thread_id, 0);
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
	if (gldata->state_mutex_arr)
	{
		i = 0;
		while (i < gldata->philodata->philo_count)
		{
			pthread_mutex_destroy(gldata->state_mutex_arr + i);
			i++;
		}
		free(gldata->state_mutex_arr);
	}
	if (gldata->philodata)
	{
		pthread_mutex_destroy(gldata->philodata->simul_mutex);
		free(gldata->philodata->simul_mutex);
		free(gldata->philodata);
	}
	free(gldata);
}
