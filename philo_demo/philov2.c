/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamaib <mohamaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:42:48 by mohamaib          #+#    #+#             */
/*   Updated: 2026/01/29 21:00:25 by mohamaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_threads(t_data *data);
void	set_dead(t_data *data);

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000);
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

int	ate_enough(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	if (philo->data->meal_count
		&& philo->eaten_meals == philo->data->meal_count)
		{
			pthread_mutex_unlock(&philo->meal_mutex);
			return (1);
		}
	pthread_mutex_unlock(&philo->meal_mutex);
	return (0);
}

void	is_sleeping(t_philo *phi)
{
	long	timestamp;

	if(phi->data->stop)
		return;
	pthread_mutex_lock(&phi->data->print_mutex);
	timestamp = get_time_ms() - phi->data->start_time;
	printf("%ld : %d is sleeping\n", timestamp, phi->id + 1);
	pthread_mutex_unlock(&phi->data->print_mutex);
	usleep(phi->data->tts * 1000);
}

void	perform_lock(t_philo *philo, pthread_mutex_t *first,
		pthread_mutex_t *sec)
{
	long	timestamp;

	pthread_mutex_lock(first);
	pthread_mutex_lock(sec);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time_ms();
	philo->eaten_meals++;
	pthread_mutex_unlock(&philo->meal_mutex);
	pthread_mutex_lock(&philo->data->print_mutex);
	timestamp = get_time_ms() - philo->data->start_time;
	printf("%ld : %d is eating\n", timestamp, philo->id + 1);
	pthread_mutex_unlock(&philo->data->print_mutex);
	usleep(philo->data->tte * 1000);
	pthread_mutex_unlock(sec);
	pthread_mutex_unlock(first);
}

void	is_eating(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	if(philo->data->stop)
		return;
	id = philo->id;
	left_fork = &philo->data->philos[id].fork;
	right_fork = &philo->data->philos[(id + 1) % philo->data->count].fork;
	if (id % 2 == 0)
	{
		first_fork = left_fork;
		second_fork = right_fork;
	}
	else
	{
		first_fork = right_fork;
		second_fork = left_fork;
	}
	perform_lock(philo, first_fork, second_fork);
}

void	is_thinking(t_philo *phi)
{
	long	timestamp;

	if(phi->data->stop)
		return;
	pthread_mutex_lock(&phi->data->print_mutex);
	timestamp = get_time_ms() - phi->data->start_time;
	printf("%ld : %d is thinking\n", timestamp, phi->id + 1);
	pthread_mutex_unlock(&phi->data->print_mutex);
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

void	monitor(t_data *data, t_gc *gc)
{
	int		i;
	long	now;
	long	last_meal;
	long	timestmp;

	while (!data->stop)
	{
		i = 0;
		while (i < data->count)
		{
			pthread_mutex_lock(&data->philos[i].meal_mutex);
			last_meal = data->philos[i].last_meal;
			now = get_time_ms();
			pthread_mutex_unlock(&data->philos[i].meal_mutex);
			if ((now - last_meal) >= data->ttd)
			{
				set_dead(data);
				timestmp = get_time_ms() - data->start_time;
				pthread_mutex_lock(&data->print_mutex);
				printf("%ld : %d has died\n", timestmp, data->philos[i].id + 1);
				pthread_mutex_unlock(&data->print_mutex);
				handle_exit(data, gc);
				break ;
			}
			i++;
		}
		usleep(1000);
	}
}

void	*simulate(void *philo)
{
	t_philo	*thread_philo;

	thread_philo = (t_philo *)philo;
	if (thread_philo->id % 2 == 0)
		usleep(1000);
	while (!check_death(thread_philo))
	{
		is_eating(thread_philo);
		if (check_death(thread_philo) || ate_enough(thread_philo))
			break ;
		is_sleeping(thread_philo);
		is_thinking(thread_philo);
		usleep(1000);
	}
	return (NULL);
}

// void	cleanup_and_exit(t_philo *philo, t_data *data)
// {
// 	free(philo);
// 	free(data);
// 	exit(1);
// }

// void	*routine(void *philo)
// {
// 	t_philo	*thread_philo;

// 	thread_philo = (t_philo *)philo;
// 	printf("hello from %d\n", thread_philo->id);
// }

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
	data = data;
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

int	main(int argc, char **argv)
{
	int		i;
	long	now;
	t_data	*data;
	t_gc	gc;

	if (argc != 5 && argc != 6)
		return (1);
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
