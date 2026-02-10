/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamaib <mohamaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 17:08:43 by mohamaib          #+#    #+#             */
/*   Updated: 2026/01/27 15:22:19 by mohamaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long get_time_ms(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000L + tv.tv_usec / 1000);
}

void	is_sleeping(t_philo *phi)
{
	printf("%d is sleeping\n", phi->id);
	usleep(phi->tts * 1000);
}

void	is_eating(t_philo *phi)
{
	phi->last_meal = get_time_ms();
	printf("%d is eating\n", phi->id);
	usleep(phi->tte * 1000);
}

void	is_thinking(t_philo *phi)
{
	printf("%d is thinking\n", phi->id);
}

int		stop_simulation(t_philo *phi)
{
	phi->now = get_time_ms();
	if(phi->now - phi->last_meal >= phi->ttd)
		return (1);
	usleep(500);
	return (0);
}

void	*monitor(void *philo)
{
	int 	i;
	t_philo	*phi;

	i = 0;
	phi = (t_philo *)philo;
	if(!stop_simulation(phi))
		return (NULL);
	printf("%d has died\n", phi->id);
	exit(1);
}

void	*simulate(void *philo)
{
	int nb;
	int i;
	t_philo *phi;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;

	phi = philo;
	nb = phi->size;
	i = phi->id - 1;
	left_fork = &phi->philos[i].fork;
	right_fork = &phi->philos[(i + 1) % nb].fork;
	if(phi->id % 2 == 0)
	{
		usleep(1000);
		pthread_mutex_lock(left_fork);
		pthread_mutex_lock(right_fork);
		printf("%d has taken a fork\n", phi->id);
		is_eating(phi);
		pthread_mutex_unlock(right_fork);
		pthread_mutex_unlock(left_fork);
	}
	else
	{
		// usleep(500);
		pthread_mutex_lock(right_fork);	
		pthread_mutex_lock(left_fork);
		printf("%d has taken a fork\n", phi->id);
		is_eating(phi);
		pthread_mutex_unlock(left_fork);
		pthread_mutex_unlock(right_fork);
	}
	is_sleeping(phi);
	is_thinking(phi);
	return (NULL);
}

void	init_vars(t_philo *philo, t_philo *philos, int argc, char **argv)
{
	philo->id = 1;
	philo->size = ft_atoi(argv[1]);
	philo->ttd = ft_atoi(argv[2]);
	philo->tte = ft_atoi(argv[3]);
	philo->tts = ft_atoi(argv[4]);
	if(argc == 5)
		philo->eatnum = 0;
	else
		philo->eatnum = ft_atoi(argv[5]);
	philo->philos = philos;
}

void	init_philos(t_philo *philo, int argc, char **argv, int size)
{
	int	i;

	i = 0;
	while(i < size - 1)
	{
		init_vars(&philo[i], philo, argc, argv);
		pthread_mutex_init(&(philo[i].fork), NULL);
		i++;
	}
	pthread_mutex_init(&(philo[i].fork), NULL);
	i = 0;
	while(i < size - 1)
	{
		philo[i].id = i + 1;
		pthread_create(&(philo[i].thread), NULL, &simulate, &philo[i]);
		i++;
	}
	pthread_create(&(philo[i].thread), NULL, &monitor, philo);
	i = 0;
	pthread_join(philo[size].thread, NULL);
	while(i < size)
	{
		if(pthread_join(philo[i].thread, NULL) != 0)
		{
			printf("error\n");
			exit (1);
		}
		i++;
	}
	i = 0;
	while(i < size)
	{
		pthread_mutex_destroy(&(philo[i].fork));
		i++;
	}
}

int main(int argc, char **argv)
{
	t_philo	*philo;
	int		size;
	
	if(argc != 5 && argc != 6)
		return (1);
	size = ft_atoi(argv[1]);
	philo = malloc(sizeof(t_philo) * size + 1);
	while(1)
	{
		init_philos(philo, argc, argv, size);
		free(philo);
	}
	// for(int i = 0; i < size; i++)
	// {
	// 	printf("philo at indx : %d, i is %d\n", philo[i].id, i);
	// }
	return (0);
}
