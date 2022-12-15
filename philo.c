/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiez-ga <sdiez-ga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:51:33 by sdiez-ga          #+#    #+#             */
/*   Updated: 2022/12/13 17:53:46 by sdiez-ga         ###   ########.fr       */
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
	{
		free_philodata(*pd);
		return (0);
	}
	*gld = init_gldata(*pd);
	if (!*gld)
	{
		free_philodata(*pd);
		return (0);
	}
	error_comp = populate_mutex_arrays(*gld);
	error_comp += populate_philo_array(*gld);
	if (error_comp != 2)
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
	int		i;

	while (is_simul_active(gld->philodata))
	{
		i = -1;
		while (++i < gld->philodata->philo_count)
		{
			pthread_mutex_lock(gld->philo_arr[i]->state_mutex);
			if (get_time_ms() - gld->philo_arr[i]->start_time - \
				gld->philo_arr[i]->lte > gld->philodata->tm_die \
				|| gld->philo_arr[i]->state == 0)
			{
				gld->philo_arr[i]->state = 0;
				pthread_mutex_lock(gld->philo_arr[i]->philodata->simul_mutex);
				gld->philodata->simul_active = 0;
				pthread_mutex_unlock(gld->philo_arr[i]->philodata->simul_mutex);
				pthread_mutex_unlock(gld->philo_arr[i]->state_mutex);
				break ;
			}
			pthread_mutex_unlock(gld->philo_arr[i]->state_mutex);
		}
	}
	i = -1;
	while (++i < gld->philodata->philo_count)
		pthread_join(gld->philo_arr[i]->thread_id, 0);
}
