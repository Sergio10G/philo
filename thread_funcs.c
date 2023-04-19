/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiez-ga <sdiez-ga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:10:59 by sdiez-ga          #+#    #+#             */
/*   Updated: 2023/04/19 18:21:49 by sdiez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

long int	philo_action(t_philo *p, char *action_msg, char *color)
{
	long int	t;

	t = get_time_ms() - p->philodata->start_time;
	pthread_mutex_lock(p->philodata->print_mutex);
	if (p->philodata->printable)
	{
		ft_putstr(color);
		ft_putlong(t);
		write(1, "\t", 1);
		ft_putlong(p->index);
		write(1, " ", 1);
		ft_putstr(action_msg);
		ft_putstr(C_RESET);
		write(1, "\n", 1);
	}
	pthread_mutex_unlock(p->philodata->print_mutex);
	return (t);
}

void	announce_death(t_philo *p)
{
	if (p->philodata->printable == 0)
		return ;
	pthread_mutex_lock(p->philodata->simul_mutex);
	if (p->philodata->simul_active == 0)
		return ;
	p->philodata->simul_active = 0;
	pthread_mutex_unlock(p->philodata->simul_mutex);
	ft_putstr(C_RED);
	ft_putlong(get_time_ms() - p->philodata->start_time);
	write(1, "\t", 1);
	ft_putlong(p->index);
	ft_putstr(" died");
	ft_putstr(C_RESET);
	write(1, "\n", 1);
}

void	*thread_routine(void *arg)
{
	t_philo		*p;

	p = (t_philo *)arg;
	while (simul_and_philo_alive(p))
	{
		philo_action(p, "is thinking", C_GREEN);
		if (!simul_and_philo_alive(p))
			break ;
		if (!eat_routine(p))
			break ;
		p->times_eaten += 1;
		if (p->times_eaten == p->philodata->eat_times_count)
			break ;
		if (!simul_and_philo_alive(p))
			break ;
		if (!sleep_routine(p))
			break ;
	}
	pthread_mutex_lock(p->state_mutex);
	if (p->state && p->philodata->eat_times_count != -1)
		p->state = 2;
	pthread_mutex_unlock(p->state_mutex);
	return (0);
}

int	eat_routine(t_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	philo_action(p, "has taken a fork", C_CYAN);
	if (!p->right_fork)
	{
		sleep_ms(p->philodata->tm_die);
		pthread_mutex_lock(p->state_mutex);
		p->state = 0;
		pthread_mutex_unlock(p->state_mutex);
		pthread_mutex_unlock(p->left_fork);
		return (0);
	}
	if (!simul_and_philo_alive(p))
	{
		pthread_mutex_unlock(p->left_fork);
		return (0);
	}
	pthread_mutex_lock(p->right_fork);
	philo_action(p, "has taken a fork", C_CYAN);
	pthread_mutex_lock(p->lte_mutex);
	pthread_mutex_lock(p->state_mutex);
	p->lte = philo_action(p, "is eating", C_BLUE);
	pthread_mutex_unlock(p->state_mutex);
	pthread_mutex_unlock(p->lte_mutex);
	return (eat_return(p));
}

int	eat_return(t_philo *p)
{
	int	ret_val;

	die_during_action(p, p->lte, p->philodata->tm_eat);
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
	pthread_mutex_lock(p->state_mutex);
	ret_val = p->state;
	pthread_mutex_unlock(p->state_mutex);
	return (ret_val);
}
