/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiez-ga <sdiez-ga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:51:43 by sdiez-ga          #+#    #+#             */
/*   Updated: 2022/11/14 16:14:35 by sdiez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//	External includes

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>

//	Consts & macros

# define C_RED		"\033[0;31m"
# define C_GREEN	"\033[0;32m"
# define C_YELLOW	"\033[0;33m"
# define C_BLUE		"\033[0;34m"
# define C_PURPLE	"\033[0;35m"
# define C_CYAN		"\033[0;36m"
# define C_RESET	"\033[0;0m"

//	Structs & types

typedef struct s_philodata
{
	int		philo_count;
	int		tm_die;
	int		tm_eat;
	int		tm_sleep;
	int		eat_times_count;
	char	simul_active;
}			t_philodata;

typedef struct s_philo
{
	int				index;
	long int		start_time;
	long int		lte;
	char			state;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_philodata		*philodata;
}					t_philo;

typedef struct s_gldata
{
	t_philodata		*philodata;
	t_philo			**philo_arr;
	pthread_mutex_t	*fork_arr;
}					t_gldata;

//	Function prototypes

//	philo.c functions
void		free_gldata(t_gldata *gldata);

//	thread_funcs.c functions
long int	philo_action(int ind, char *action_msg, char *color, long int st);
void		*thread_routine(void *arg);
int			eat_routine(t_philo *p);

//	input_parse.c functions
int			parse_input(int argc, char **argv, t_philodata *pd);

//	init_structs.c functions
t_philo		*init_philo(t_philodata *pd, pthread_mutex_t *fork_arr, int index);
t_philodata	*init_philodata();
t_gldata	*init_gldata(t_philodata *pd);
int			populate_fork_array(t_gldata *gld);
int			populate_philo_array(t_gldata *gld);

//	utils.c functions
int			ft_strlen(char *str);
int			ft_isspace(char c);
int			ft_atoi(const char *str);
int			is_all_numeric(char *num_str);

//	utils_2.c functions
void		sleep_ms(int ms);
long int	get_time_ms();
pthread_mutex_t	*get_fork(int i, pthread_mutex_t *fork_arr, int arr_size);

#endif
