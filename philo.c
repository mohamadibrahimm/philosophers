/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamaib <mohamaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:42:48 by mohamaib          #+#    #+#             */
/*   Updated: 2026/01/30 17:24:31 by mohamaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000);
}

int	ate_enough(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	if (philo->data->meal_count != -1
		&& philo->eaten_meals >= philo->data->meal_count)
	{
		pthread_mutex_unlock(&philo->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	return (0);
}

void	done_eating(t_data *data, t_gc *gc)
{
	set_dead(data);
	handle_exit(data, gc);
}

void	monitor(t_data *data, t_gc *gc)
{
	int		i;
	long	last_meal;

	while (!data->stop)
	{
		i = 0;
		while (i < data->count)
		{
			pthread_mutex_lock(&data->philos[i].meal_mutex);
			last_meal = data->philos[i].last_meal;
			pthread_mutex_unlock(&data->philos[i].meal_mutex);
			if ((get_time_ms() - last_meal) >= data->ttd)
			{
				handle_death(data, gc, i);
				break ;
			}
			i++;
		}
		if (all_ate_enough(data))
			done_eating(data, gc);
		usleep(1000);
	}
}

int	main(int argc, char **argv)
{
	int		i;
	t_data	*data;
	t_gc	gc;

	if ((argc != 5 && argc != 6) || check_syntax(argv))
	{
		printf("Invalid arguments\n");
		return (1);
	}
	i = 0;
	gc_init(&gc);
	data = gc_malloc(sizeof(t_data), &gc);
	init_args(data, argc, argv, &gc);
	init_mutexes(data);
	init_threads(data);
	monitor(data, &gc);
	join_threads(data);
	return (0);
}
