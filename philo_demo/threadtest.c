#include "philo.h"
#include <unistd.h>

void *newf()
{
	int res;
	int *retval;
	
	retval = malloc(sizeof(int));
	res = 9 + 123;
	(*retval) = res;
	return (void *)retval;
}

int main(int argc, char **argv)
{
	int i;
	int size;
	int	*res;
	if(argc != 2)
		return (1);
	i = 0;
	size = ft_atoi(argv[1]);
	pthread_t thr[size];
	pthread_mutex_t mut;

	pthread_mutex_init(&mut, NULL);
	while(i < size)
	{
		pthread_create(thr + i, NULL, &newf, NULL);
		i++;
	}
	i = 0;
	while (i < size)
	{
		pthread_join(thr[i], (void **)(&res));
		i++;
	}
	printf("%d\n", (*res));
	pthread_mutex_destroy(&mut);
	free(res);
	return (0);
}
