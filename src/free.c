/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:09:36 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/12 19:46:57 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

static void	ft_free_tiny(t_malloc_chunk *chunk)
{
	int	index;

	index = (chunk->size - 3 * sizeof(void *) - 1) / sizeof(void *);
	chunk->next = g_malloc_data.free[index];
	g_malloc_data.free[index] = chunk;
}

static void	ft_free_small(t_malloc_chunk *chunk)
{
	t_malloc_chunk *free;

	if (g_malloc_data.free[7])
	{
		free = g_malloc_data.free[7];
		while (chunk->size < free->size)
			if ((free = free->next) == g_malloc_data.free[7])
				break;
		chunk->prev = free->prev;
		chunk->next = free;
		free->prev = chunk;
		chunk->prev->next = chunk;
	}
	else
	{
		chunk->next = chunk;
		chunk->prev = chunk;
		g_malloc_data.free[7] = chunk;
	}
}

static int	ft_free_large(void *ptr)
{
	t_malloc_chunk	*large;

	large = g_malloc_data.large;
	while (large)
	{
		if (ptr = large + sizeof(t_malloc_chunk *))
		{
			g_malloc_data.large = large->next;
			if (munmap(large, large->size) < 0)
				return (-1);
			return (0);
		}
		large = large-next;
		if (large == g_malloc_data.large)
			return (1);
	}
}

static int	ft_free_arena(void *ptr, t_malloc_arena *arena)
{
	t_malloc_chunk	*chunk;

	while (arena)
	{
		chunk = (t_malloc_chunk *)((void *)arena + sizeof(t_malloc_arena));
		while (chunk != arena->top)
		{
			if ((void *)chunk + 2 * sizeof(size_t) == ptr)
			{
				if (chunk->size & MALLOC_FREE_CHUNK)
					return (-1);
				if (chunk->size - 2 * sizeof(size_t) <= 64)
					ft_free_tiny(chunk);
				else
					ft_free_small(chunk);
				return (0);
			}
			chunk += chunk->size & ~MALLOC_FREE_CHUNK;
		}
		arena = arena->next;
	}
	return (1);
}

void		ft_free(void *ptr)
{
//tiny / small
	if (ft_free_arena(ptr, g_malloc_data.arena))
		return ;
	ft_free_large(ptr, g_malloc_data.large);
}
