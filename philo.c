/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiez-ga <sdiez-ga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:51:33 by sdiez-ga          #+#    #+#             */
/*   Updated: 2023/03/07 18:28:56 by sdiez-ga         ###   ########.fr       */
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
	int	error_comp;

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
	error_comp += populate_philo_arrays(*gld);
	assign_mutexes(*gld);
	if (error_comp != 2)
	{
		free_gldata(*gld);
		return (0);
	}
	return (1);
}

void	launch_phase(t_gldata *gld)
{
	t_philo			*p;
	t_ph_monitor	*pm;
	long int		time;
	int				i;

	time = get_time_ms();
	i = 0;
	while (i < gld->philodata->philo_count)
	{
		pm = gld->ph_monitor_arr[i];
		p = gld->philo_arr[i];
		p->start_time = time;
		pthread_create(&(pm->thread_id), 0, &monitor_routine, pm);
		usleep(100);
		i++;
	}
}

void	simulation_phase(t_gldata *gld)
{
	int	i;

	while (is_simul_active(gld->philodata))
	{
		finish_if_everyone_full(gld);
		sleep_ms(gld->philodata->tm_eat);
	}
	i = -1;
	while (++i < gld->philodata->philo_count)
		pthread_join(gld->ph_monitor_arr[i]->thread_id, 0);
}

void	announce_death(t_philo *p)
{
	ft_putstr(C_RED);
	ft_putlong(get_time_ms() - p->start_time);
	write(1, "\t", 1);
	ft_putlong(p->index + 1);
	ft_putstr(" died");
	ft_putstr(C_RESET);
	write(1, "\n", 1);
	// printf("%s%ld\t%d died%s\n", C_RED, get_time_ms() - p->start_time, \
	// p->index + 1, C_RESET);
}
