/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamaib <mohamaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:15:37 by mohamaib          #+#    #+#             */
/*   Updated: 2026/01/30 16:41:08 by mohamaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_ate_enough(t_data *data)
{
	int	i;
	int	done;

	if (data->meal_count == -1)
		return (0);
	i = 0;
	done = 1;
	while (i < data->count)
	{
		pthread_mutex_lock(&data->philos[i].meal_mutex);
		if (data->philos[i].eaten_meals < data->meal_count)
			done = 0;
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		if (!done)
			break ;
		i++;
	}
	return (done);
}

void	handle_death(t_data *data, t_gc *gc, int i)
{
	long	timestmp;

	pthread_mutex_lock(&data->print_mutex);
	timestmp = get_time_ms() - data->start_time;
	printf("%ld %d died\n", timestmp, data->philos[i].id + 1);
	pthread_mutex_unlock(&data->print_mutex);
	set_dead(data);
	handle_exit(data, gc);
}

void	set_dead(t_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	data->stop = 1;
	pthread_mutex_unlock(&data->stop_mutex);
}

int	check_death(t_philo *philo)
{
	int	flag;

	pthread_mutex_lock(&philo->data->stop_mutex);
	flag = philo->data->stop;
	pthread_mutex_unlock(&philo->data->stop_mutex);
	return (flag);
}

void	handle_exit(t_data *data, t_gc *gc)
{
	int	i;

	i = 0;
	join_threads(data);
	while (i < data->count)
	{
		pthread_mutex_destroy(&data->philos[i].fork);
		pthread_mutex_destroy(&data->philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->stop_mutex);
	gc_free_all(gc);
	exit(0);
}
