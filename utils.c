/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiez-ga <sdiez-ga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:36:31 by sdiez-ga          #+#    #+#             */
/*   Updated: 2022/11/09 18:25:37 by sdiez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ');
}

int	ft_atoi(const char *str)
{
	size_t	u_val;
	size_t	i;
	int		sign;

	u_val = 0;
	i = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		u_val = (u_val * 10) + (str[i] - '0');
		if (u_val > 2147483647 && sign == 1)
			return (-1);
		if (u_val > 2147483648 && sign == -1)
			return (0);
		i++;
	}
	return (u_val * sign);
}

int	is_all_numeric(char *num_str)
{
	int	i;

	i = 0;
	while (num_str[i])
	{
		if (num_str[i] != '-' && !(num_str[i] >= '0' && num_str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}
