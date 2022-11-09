/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiez-ga <sdiez-ga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:51:43 by sdiez-ga          #+#    #+#             */
/*   Updated: 2022/11/09 19:59:00 by sdiez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//	External includes

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <string.h>

//	Consts & macros

//	Structs & types

typedef struct s_philodata
{
	int		philo_count;
	int		tm_die;
	int		tm_eat;
	int		tm_sleep;
	int		eat_times_count;
}			t_philodata;

typedef struct s_philo
{
	int				start_time;
	int				index;
	int				last_time_eaten;
	pthread_t		thread_id;
	pthread_mutex_t	*fork_arr;
	t_philodata		*philodata;
}					t_philo;

typedef struct s_gldata
{
	t_philodata		*philodata;
	t_philo			**philo_arr;
	pthread_mutex_t	*fork_arr;
}					t_gldata;

//	Function prototypes

//	input_parse.c functions
int			parse_input(int argc, char **argv, t_philodata *pd);

//	philo.c functions
void		free_gldata(t_gldata *gldata);

//	init_structs.c functions
t_philo		*init_philo(t_philodata *pd, pthread_mutex_t *fork_arr, int index);
t_philodata	*init_philodata();
t_gldata	*init_gldata(t_philodata *pd);
int			populate_fork_array(t_gldata *gld);
int			populate_philo_array(t_gldata *gld);

//	print_funcs.c
void	print_str(char *str);
size_t	itoa_off(char *num_str, unsigned int un, int sign);
void	print_nbr(int n);

//	utils.c functions
int			ft_strlen(char *str);
int			ft_isspace(char c);
int			ft_atoi(const char *str);
int			is_all_numeric(char *num_str);

#endif
