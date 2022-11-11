/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiez-ga <sdiez-ga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:51:33 by sdiez-ga          #+#    #+#             */
/*   Updated: 2022/11/11 14:38:10 by sdiez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	main(int argc, char **argv)
{
	t_philodata	*pd;
	t_gldata	*gld;
	int			correct_parse;
	int			error_comp;

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
	long int time = get_time_ms();
	for (int i = 0; i < gld->philodata->philo_count; i++)
	{
		gld->philo_arr[i]->start_time = time;
		pthread_create(&(gld->philo_arr[i]->thread_id), 0, &thread_routine, gld->philo_arr[i]);
		//pthread_join(gld->philo_arr[i]->thread_id, 0);
	}
	int 	i;
	while (1)
	{
		i = 0;
		while (i < gld->philodata->philo_count)
		{
			if (get_time_ms() - gld->philo_arr[i]->start_time - gld->philo_arr[i]->last_time_eaten > gld->philodata->tm_die)
			{
				gld->philo_arr[i]->state = 0;
				gld->philodata->simul_active = 0;
				pthread_join(gld->philo_arr[i]->thread_id, 0);
				break ;
			}
		}
		if (!gld->philodata->simul_active)
		{
			// free all
			printf("MAIN THREAD STOPPED\n");
			break ;
		}
	}
	
}

//	FIXME
void	free_gldata(t_gldata *gldata)
{
	int	i;

	if (gldata->philodata)
		free(gldata->philodata);
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
	free(gldata);
}
