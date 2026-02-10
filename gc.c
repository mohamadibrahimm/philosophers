/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamaib <mohamaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 17:46:41 by mohamaib          #+#    #+#             */
/*   Updated: 2026/01/30 17:46:43 by mohamaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	gc_init(t_gc *gc)
{
	gc->list = NULL;
}

void	*gc_malloc(size_t size, t_gc *gc)
{
	void		*ptr;
	t_gc_node	*node;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	node = malloc(sizeof(t_gc_node));
	if (!node)
	{
		free(ptr);
		return (NULL);
	}
	node->ptr = ptr;
	node->next = gc->list;
	gc->list = node;
	return (ptr);
}

void	gc_free_all(t_gc *gc)
{
	t_gc_node	*cur;
	t_gc_node	*next;

	cur = gc->list;
	while (cur)
	{
		next = cur->next;
		free(cur->ptr);
		free(cur);
		cur = next;
	}
	gc->list = NULL;
}
