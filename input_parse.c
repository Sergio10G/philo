/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiez-ga <sdiez-ga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:30:32 by sdiez-ga          #+#    #+#             */
/*   Updated: 2022/12/13 18:29:57 by sdiez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	parse_input(int argc, char **argv, t_philodata *pd)
{
	int	i;
	int	nums[5];
	int	parsed_num;

	if (argc < 5 || argc > 6)
		return (0);
	nums[4] = -1;
	i = 1;
	while (i < argc)
	{
		parsed_num = ft_atoi(argv[i]);
		if (parsed_num < 0 || (parsed_num == 0 && ft_strlen(argv[i]) != 1) || \
			(parsed_num == 0 && ft_strlen(argv[i]) == 1 && \
			argv[i][0] != '0') || !is_all_numeric(argv[i]))
			return (0);
		nums[i - 1] = parsed_num;
		i++;
	}
	pd->simul_active = 1;
	pd->philo_count = nums[0];
	pd->tm_die = nums[1];
	pd->tm_eat = nums[2];
	pd->tm_sleep = nums[3];
	pd->eat_times_count = nums[4];
	return (1);
}
