/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamaib <mohamaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 17:08:04 by mohamaib          #+#    #+#             */
/*   Updated: 2026/01/30 16:31:57 by mohamaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_gc_node
{
	void				*ptr;
	struct s_gc_node	*next;
}						t_gc_node;

typedef struct s_gc
{
	t_gc_node			*list;
}						t_gc;

typedef struct s_data
{
	int					count;
	long				ttd;
	long				tte;
	long				tts;
	int					meal_count;
	long				start_time;
	int					stop;
	pthread_mutex_t		stop_mutex;
	pthread_mutex_t		print_mutex;
	struct s_philo		*philos;
}						t_data;

typedef struct s_philo
{
	int					id;
	int					eaten_meals;
	long				last_meal;
	pthread_t			thread;
	pthread_mutex_t		fork;
	pthread_mutex_t		meal_mutex;
	t_data				*data;
}						t_philo;

/* gc.c */
void					gc_init(t_gc *gc);
void					*gc_malloc(size_t size, t_gc *gc);
void					gc_free_all(t_gc *gc);

/* philo.c */
int						ate_enough(t_philo *philo);
long					get_time_ms(void);

/* init.c */
void					init_threads(t_data *data);
void					init_mutexes(t_data *data);
void					init_args(t_data *data, int argc, char **argv,
							t_gc *gc);
void					join_threads(t_data *data);

/* simulate.c */
void					*simulate(void *philo);

/* simulate_utils.c */
void					lock_forks(pthread_mutex_t *sec,
							pthread_mutex_t *first);
void					lock_meals(t_philo *philo);
void					perform_lock(t_philo *philo, pthread_mutex_t *first,
							pthread_mutex_t *sec);
void					handle_single_philo(t_philo *philo);
void					is_eating(t_philo *philo);

/* simulate_utils2.c */
void					is_sleeping(t_philo *phi);
void					is_thinking(t_philo *phi);

/* philo_utils.c */
int						ft_atoi(const char *str);
void					print_status(t_philo *phi, char *status);
int						check_syntax(char **argv);

/* exit.c */
int						all_ate_enough(t_data *data);
void					handle_death(t_data *data, t_gc *gc, int i);
void					set_dead(t_data *data);
int						check_death(t_philo *philo);
void					handle_exit(t_data *data, t_gc *gc);

#endif