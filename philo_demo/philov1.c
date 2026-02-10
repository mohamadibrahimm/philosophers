/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamaib <mohamaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:45:40 by mohamaib          #+#    #+#             */
/*   Updated: 2026/01/17 21:26:31 by mohamaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_lst(t_philo *philo)
{
	t_philo	*tmp;

	tmp = philo;
	while(tmp->next)
	{
		printf("i am philo number %d, ", tmp->philo_index);
		printf("my previous is %d, ", tmp->previous->philo_index);
		tmp = tmp->next;
		printf("my next is %d\n", tmp->philo_index);
		if(tmp->philo_index == 1)
			break;
	}
}

t_data	*init_data(t_philo *philo, char **argv, int argc)
{
	philo->data.ttd = ft_atoi(argv[2]);
	philo->data.tte = ft_atoi(argv[3]);
	philo->data.tts = ft_atoi(argv[4]);
	if (argc == 5)
		philo->data.eatnum = 0;
	else
		philo->data.eatnum = ft_atoi(argv[5]);
	return (&(philo->data));
}

void	add_to_list(t_philo **philo, t_data *data, int index)
{
	t_philo	*new;
	t_philo	*tmp;

	new = malloc(sizeof(t_philo));
	new->philo_index = index;
	new->data = (*data);
	new->next = NULL;
	new->previous = NULL;
	if(!new)
	{
		(*philo) = new;
		return ;
	}
	tmp = (*philo);
	while(tmp->next)
	{
		if(tmp->next->philo_index == 1)
			break ;
		tmp = tmp->next;
	}
	tmp->next = new;
	new->next = (*philo);
	(*philo)->previous = new;
	new->previous = tmp;
	return ;
}

int main(int argc, char **argv)
{
	t_philo *philo;
	t_data	*data;
	int		i;
	int		phicount;

	if (argc > 6 || argc < 5)
		return (1);
	phicount = ft_atoi(argv[1]);
	if(phicount < 1)
	{
		printf("invalid number of philosophers\n");
		return (1);
	}
	philo = malloc(sizeof(t_philo));
	data = init_data(philo, argv, argc);
	philo->philo_index = 1;
	i = 1;
	while(i < phicount)
	{
		add_to_list(&philo, data, i + 1);
		i++;
	}
	print_lst(philo);
}
