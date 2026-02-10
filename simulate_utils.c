/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamaib <mohamaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:13:05 by mohamaib          #+#    #+#             */
/*   Updated: 2026/01/30 16:09:11 by mohamaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock_forks(pthread_mutex_t *sec, pthread_mutex_t *first)
{
	pthread_mutex_unlock(sec);
	pthread_mutex_unlock(first);
}

void	lock_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time_ms();
	philo->eaten_meals++;
	pthread_mutex_unlock(&philo->meal_mutex);
}

void	perform_lock(t_philo *philo, pthread_mutex_t *first,
		pthread_mutex_t *sec)
{
	pthread_mutex_lock(first);
	if (check_death(philo))
	{
		pthread_mutex_unlock(first);
		return ;
	}
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(sec);
	if (check_death(philo))
	{
		unlock_forks(sec, first);
		return ;
	}
	print_status(philo, "has taken a fork");
	if (check_death(philo))
	{
		unlock_forks(sec, first);
		return ;
	}
	lock_meals(philo);
	print_status(philo, "is eating");
	usleep(philo->data->tte * 1000);
	pthread_mutex_unlock(sec);
	pthread_mutex_unlock(first);
}

void	handle_single_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->philos[0].fork);
	print_status(philo, "has taken a fork");
	while (!check_death(philo))
		usleep(1000);
	pthread_mutex_unlock(&philo->data->philos[0].fork);
	return ;
}

void	is_eating(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	int				id;

	if (check_death(philo))
		return ;
	if (philo->data->count == 1)
	{
		handle_single_philo(philo);
		return ;
	}
	id = philo->id;
	if (id % 2 == 0)
	{
		first_fork = &philo->data->philos[id].fork;
		second_fork = &philo->data->philos[(id + 1) % philo->data->count].fork;
	}
	else
	{
		first_fork = &philo->data->philos[(id + 1) % philo->data->count].fork;
		second_fork = &philo->data->philos[id].fork;
	}
	perform_lock(philo, first_fork, second_fork);
}
