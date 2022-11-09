/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiez-ga <sdiez-ga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:51:33 by sdiez-ga          #+#    #+#             */
/*   Updated: 2022/11/09 20:05:58 by sdiez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	*thread_function(void *arg)
{
	t_philo	*philo;

	if (arg == 0)
	{
		printf("Philo without data \n");
		return 0;
	}
	philo = (t_philo*)arg;
	printf("Yo! I'm a philo, this is my data:\n");
	printf("\tstart_time: %d\n", philo->start_time);
	printf("\tindex: %d\n", philo->index);
	printf("\tthread_id: %p\n", &(philo->thread_id));
	printf("\tfork_arr: %p\n", philo->fork_arr);
	printf("\tphilodata: %p\n", philo->philodata);
	printf("\t\tphilo_count: %d\n", philo->philodata->philo_count);
	printf("\t\ttm_die: %d\n", philo->philodata->tm_die);
	printf("\t\ttm_eat: %d\n", philo->philodata->tm_eat);
	printf("\t\ttm_sleep: %d\n", philo->philodata->tm_sleep);
	printf("\t\teat_times_count: %d\n", philo->philodata->eat_times_count);
	return 0;
}

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
	for (int i = 0; i < gld->philodata->philo_count; i++)
	{
		pthread_create(&(gld->philo_arr[i]->thread_id), 0, &thread_function, gld->philo_arr[i]);
		pthread_join(gld->philo_arr[i]->thread_id, 0);
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
