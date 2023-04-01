/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiez-ga <sdiez-ga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:51:43 by sdiez-ga          #+#    #+#             */
/*   Updated: 2023/04/01 19:45:16 by sdiez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//	External includes

# include <pthread.h>
# include <unistd.h>
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
# define C_GRAY		"\033[2;37m"
# define C_RESET	"\033[0;0m"

# define PHILOS_PER_MONITOR 10

//	Structs & types

typedef struct s_philodata
{
	int				philo_count;
	int				tm_die;
	int				tm_eat;
	int				tm_sleep;
	int				eat_times_count;
	char			simul_active;
	long int		start_time;
	pthread_mutex_t	*simul_mutex;
}			t_philodata;

typedef struct s_philo
{
	int				index;
	long int		lte;
	int				times_eaten;
	char			state;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*state_mutex;
	pthread_mutex_t	*lte_mutex;
	t_philodata		*philodata;
}					t_philo;

typedef struct s_ph_monitor
{
	void			*void_gld;
	pthread_t		thread_id;
	int				index;
}					t_ph_monitor;

typedef struct s_gldata
{
	t_philodata		*philodata;
	t_philo			**philo_arr;
	t_ph_monitor	**ph_monitor_arr;
	pthread_mutex_t	*fork_arr;
	pthread_mutex_t	*state_mutex_arr;
	pthread_mutex_t	*lte_mutex_arr;
	pthread_mutex_t	*monitor_mutex;
}					t_gldata;

//	Function prototypes

//	philo.c functions
int				alloc_phase(int argc, char **argv, \
							t_philodata **pd, t_gldata **gld);
void			launch_phase(t_gldata *gld);
void			simulation_phase(t_gldata *gld);
void			announce_death(t_philo *p);

//	free_funcs.c functions
void			free_gldata(t_gldata *gldata);
void			free_philo_array(t_gldata *gld);
void			free_monitor_array(t_gldata *gld);
void			free_mutex_arrays(t_gldata *gld);
void			free_philodata(t_philodata *pd);

//	thread_funcs.c functions
long int		philo_action(t_philo *p, char *action_msg, char *color);
void			*thread_routine(void *arg);
int				eat_routine(t_philo *p);
int				sleep_routine(t_philo *p);

// thread_funcs_2.c functions
int				eat_return(t_philo *p);
void			*monitor_routine(void *arg);

//	control_funcs.c functions
int				is_simul_active(t_philodata *pd);
int				simul_and_philo_alive(t_philo *p);
int				check_death_main(t_philo *p);
void			finish_if_everyone_full(t_gldata *gld);
int				die_during_action(t_philo *p, long int now, int action_time);

//	input_parse.c functions
int				parse_input(int argc, char **argv, t_philodata *pd);

//	init_structs.c functions
t_philo			*init_philo(t_philodata *pd, int index);
t_philodata		*init_philodata(void);
t_gldata		*init_gldata(t_philodata *pd);
int				populate_mutex_arrays(t_gldata *gld);
int				populate_philo_arrays(t_gldata *gld);

//	init_structs_2.c functions
void			assign_mutexes(t_gldata *gld);
t_ph_monitor	*init_ph_monitor(t_gldata *gld);

//	utils.c functions
int				ft_strlen(char *str);
int				ft_isspace(char c);
int				ft_atoi(const char *str);
int				is_all_numeric(char *num_str);
pthread_mutex_t	*get_fork(int i, pthread_mutex_t *fork_arr, int arr_size);

//	utils_2.c functions
void			sleep_ms(int ms);
long int		get_time_ms(void);
void			ft_putstr(char *str);
void			ft_putlong(long int n);
char			*rev_num(char *temp, int last_pos);

#endif
