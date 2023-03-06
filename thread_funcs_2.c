/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_funcs_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiez-ga <sdiez-ga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:51:01 by sdiez-ga          #+#    #+#             */
/*   Updated: 2023/03/06 14:51:17 by sdiez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	eat_return(t_philo *p)
{
	int	ret_val;

	pthread_mutex_lock(p->state_mutex);
	ret_val = p->state;
	pthread_mutex_unlock(p->state_mutex);
	return (ret_val);
}
