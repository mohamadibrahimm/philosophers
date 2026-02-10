/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamaib <mohamaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:45:59 by mohamaib          #+#    #+#             */
/*   Updated: 2026/01/05 22:52:23 by mohamaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_data
{
	int				ttd;
	int				tte;
	int				tts;
	int				eatnum;
}					t_data;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	fork;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	state_mutex;
	int				philo_index;
	t_data			data;
	struct s_philo	*next;
	struct s_philo	*previous;
}					t_philo;

/* philo_utils.c */
int					ft_atoi(const char *str);

#endif