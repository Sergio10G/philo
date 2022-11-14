/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiez-ga <sdiez-ga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:51:33 by sdiez-ga          #+#    #+#             */
/*   Updated: 2022/11/14 16:47:58 by sdiez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

/*
void	leaks(void)
{
	system("leaks philo");
}
*/

int	main(int argc, char **argv)
{
	t_philodata	*pd;
	t_gldata	*gld;
	int			correct_parse;
	int			error_comp;

	//atexit(leaks);
	pd = init_philodata();
	if (!pd)
		return (1);
	correct_parse = parse_input(argc, argv, pd);
	if (!correct_parse)
		return (1);
	gld = init_gldata(pd);
	if (!gld)
	{
		free(pd);
		return (1);
	}
	error_comp = populate_fork_array(gld);
	error_comp += populate_philo_array(gld);
	// Make error_comp do something
	long int time = get_time_ms();
	for (int i = 0; i < gld->philodata->philo_count; i++)
	{
		gld->philo_arr[i]->start_time = time;
		pthread_create(&(gld->philo_arr[i]->thread_id), 0, &thread_routine, gld->philo_arr[i]);
		sleep_ms(1);
	}
	int 	i;
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
	free_gldata(gld);
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
