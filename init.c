/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamaib <mohamaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:10:24 by mohamaib          #+#    #+#             */
/*   Updated: 2026/01/29 22:17:38 by mohamaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_threads(t_data *data)
{
	int		i;
	long	start;

	i = 0;
	start = get_time_ms();
	data->start_time = start;
	while (i < data->count)
	{
		data->philos[i].id = i;
		data->philos[i].data = data;
		data->philos[i].last_meal = start;
		data->philos[i].eaten_meals = 0;
		pthread_create(&(data->philos[i].thread), NULL, &simulate,
			&data->philos[i]);
		i++;
	}
}

void	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->count)
	{
		pthread_mutex_init(&data->philos[i].fork, NULL);
		pthread_mutex_init(&data->philos[i].meal_mutex, NULL);
		i++;
	}
	pthread_mutex_init(&data->stop_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
}

void	init_args(t_data *data, int argc, char **argv, t_gc *gc)
{
	data->stop = 0;
	data->count = ft_atoi(argv[1]);
	data->ttd = ft_atoi(argv[2]);
	data->tte = ft_atoi(argv[3]);
	data->tts = ft_atoi(argv[4]);
	if (argc == 5)
		data->meal_count = -1;
	else
		data->meal_count = ft_atoi(argv[5]);
	data->philos = gc_malloc(sizeof(t_philo) * data->count, gc);
}

void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->count)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}
