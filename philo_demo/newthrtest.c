/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newthrtest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamaib <mohamaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 21:50:01 by mohamaib          #+#    #+#             */
/*   Updated: 2026/01/25 15:40:50 by mohamaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int arr[10] = {2, 3, 5, 7, 11, 13, 17, 23, 29, 31};
pthread_mutex_t mut;
int i = 0;
int indx = 1;

void *routine(void *arg)
{
	pthread_mutex_lock(&mut);
	while(arr[i])
	{
		printf("arr[i] = %d, i'm thr nb %d\n", arr[i], indx);
		i++;
		break;
	}
	int r = 4;
	int *res = malloc(sizeof(int));

	while(i < 3)
	{
		*res = (*(int *)arg) * r + *res;
		i++;
	}
	pthread_mutex_unlock(&mut);
	indx++;
	return ((void *)res);
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	int i = 0;
	int op = 1;
	int *res;
	int	size = ft_atoi(argv[1]);
	pthread_t thr[size];

	pthread_mutex_init(&mut, NULL);
	while(i < size)
	{
		if(pthread_create(&thr[i], NULL, &routine, &size) != 0)
			return (1);
		i++;
	}
	i = 0;
	while(i < size)
	{
		if(pthread_join(thr[i], (void **)&res) != 0)
			return (1);
		i++;
	}
	printf("res = %d\n", (*res));
	pthread_mutex_destroy(&mut);
	free(res);
	return (0);
}
