/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiez-ga <sdiez-ga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:46:02 by sdiez-ga          #+#    #+#             */
/*   Updated: 2022/11/09 20:07:16 by sdiez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	print_str(char *str)
{
	write(1, str, ft_strlen(str));
}

size_t	itoa_off(char *num_str, unsigned int un, int sign)
{
	size_t	i;

	i = 10;
	while (un != 0 && i > 0)
	{
		num_str[i] = un % 10 + '0';
		un /= 10;
		i--;
	}
	if (sign < 0)
	{
		num_str[i] = '-';
		i--;
	}
	return (i + 1);
}

void	print_nbr(int n)
{
	unsigned int	un;
	int				sign;
	int				offset;
	char			num_str[12];

	num_str[11] = 0;
	sign = 1;
	if (n == 0)
	{
		write(1, "0", 1);
		return ;
	}
	else if (n < 0)
	{
		un = n * -1;
		sign *= -1;
	}
	else
		un = n;
	offset = itoa_off(num_str, un, sign);
	print_str(num_str + offset);
}
