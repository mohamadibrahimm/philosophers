/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamaib <mohamaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:11:35 by mohamaib          #+#    #+#             */
/*   Updated: 2026/01/29 22:11:57 by mohamaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		if (check_death(thread_philo))
			break ;
		is_thinking(thread_philo);
		usleep(1000);
	}
	return (NULL);
}
