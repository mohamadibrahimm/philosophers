/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamaib <mohamaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:14:29 by mohamaib          #+#    #+#             */
/*   Updated: 2026/01/30 15:56:10 by mohamaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_sleeping(t_philo *phi)
{
	if (check_death(phi))
		return ;
	print_status(phi, "is sleeping");
	usleep(phi->data->tts * 1000);
}

void	is_thinking(t_philo *phi)
{
	if (check_death(phi))
		return ;
	print_status(phi, "is thinking");
}
