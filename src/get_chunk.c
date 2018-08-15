/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_chunk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 17:58:31 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/15 17:59:46 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
 
#include "malloc.h"

t_malloc_data	g_malloc_data;

static t_malloc_chunk	*get_chunk(void *ptr, t_malloc_arena *start)
{
	t_malloc_arena	*arena;
	t_malloc_chunk	*chunk;

	if (start)
	{
		arena = start;
		while (arena)
		{
			chunk = (t_malloc_chunk *)(arena + 1);
			while (chunk != arena->top)
			{
				if ((void *)chunk + 2 * sizeof(size_t) == ptr)
					return (chunk);
				if (chunk->size < 2 * sizeof(size_t) || chunk->size & 7)
				{
					if (g_malloc_data.debug_var & MALLOC_ERROR_ABORT
						|| g_malloc_data.debug_var & MALLOC_CORRUPTION_ABORT)
						abort();
					return (NULL);
				}
				chunk += chunk->size & ~MALLOC_FREE_CHUNK;
			}
			arena = arena->next;
		}
	}
	return (NULL);
}

t_malloc_chunk			*get_tiny_chunk(void *ptr)
{
	return (get_chunk(ptr, g_malloc_data.tiny));
}

t_malloc_chunk			*get_small_chunk(void *ptr)
{
	return (get_chunk(ptr, g_malloc_data.small));
}

t_malloc_chunk			*get_large_chunk(void *ptr)
{
	t_malloc_chunk	*chunk;

	chunk = g_malloc_data.large;
	while (chunk)
	{
		if ((void *)chunk + sizeof(t_malloc_chunk) == ptr)
			return (chunk);
		if ((chunk = chunk->next) == g_malloc_data.large)
			break ;
	}
	return (NULL);
}
