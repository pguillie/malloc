/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_chunk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 17:58:31 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/20 17:10:08 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

static t_malloc_chunk	*get_chunk_arena(void *ptr, t_malloc_chunk *chunk,
		t_malloc_chunk *top)
{
	size_t	size;

	while (chunk != top)
	{
		if ((void *)chunk + 2 * sizeof(size_t) == ptr)
			return (chunk);
		size = chunk->size & ~MALLOC_FREE_CHUNK;
		if (size < sizeof(t_malloc_chunk) || size & 15)
		{
			if (g_malloc_data.debug & MALLOC_VERBOSE)
				malloc_verbose("warning", "corrupted size:",
						chunk, chunk->size);
			if (g_malloc_data.debug & MALLOC_CORRUPTION_ABORT
					|| g_malloc_data.debug & MALLOC_ERROR_ABORT)
				abort();
			return (NULL);
		}
		chunk = (t_malloc_chunk *)((void *)chunk + size);
	}
	return (NULL);
}

static t_malloc_chunk	*get_chunk(void *ptr, t_malloc_arena *start)
{
	t_malloc_arena	*arena;
	t_malloc_chunk	*chunk;

	if (start)
	{
		arena = start;
		while (arena)
		{
			chunk = get_chunk_arena(ptr, (t_malloc_chunk *)(arena + 1),
					arena->top);
			if (chunk)
				return (chunk);
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
		if (chunk + 1 == ptr)
			return (chunk);
		if ((chunk = chunk->next) == g_malloc_data.large)
			break ;
	}
	return (NULL);
}
