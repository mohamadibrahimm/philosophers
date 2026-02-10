/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamaib <mohamaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 17:08:34 by mohamaib          #+#    #+#             */
/*   Updated: 2026/02/03 17:29:36 by mohamaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
		{
			sign = -1;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

void	print_status(t_philo *phi, char *status)
{
	long	timestamp;

	pthread_mutex_lock(&phi->data->stop_mutex);
	if (phi->data->stop)
	{
		pthread_mutex_unlock(&phi->data->stop_mutex);
		return ;
	}
	pthread_mutex_unlock(&phi->data->stop_mutex);
	pthread_mutex_lock(&phi->data->print_mutex);
	timestamp = get_time_ms() - phi->data->start_time;
	printf("%ld %d %s\n", timestamp, phi->id + 1, status);
	pthread_mutex_unlock(&phi->data->print_mutex);
}

int	check_syntax(char **argv)
{
	int	i;
	int	j;
	int	flag;

	i = 1;
	flag = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
