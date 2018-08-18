/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_chunk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 17:58:31 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/18 13:28:19 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
 
#include "malloc.h"

t_malloc_data	g_malloc_data;

static t_malloc_chunk	*get_chunk(void *ptr, t_malloc_arena *start)
{
	t_malloc_arena	*arena;
	t_malloc_chunk	*chunk;
	size_t			size;

	if (start)
	{
		arena = start;
		while (arena)
		{
			chunk = (t_malloc_chunk *)(arena + 1);
//			malloc_verbose("err", "top:  ", arena->top, arena->top->size);
			while (chunk != arena->top)
			{
//				malloc_verbose("err", "chunk:", chunk, chunk->size);
				if ((void *)chunk + 2 * sizeof(size_t) == ptr)
					return (chunk);
				size = chunk->size & ~MALLOC_FREE_CHUNK;
				if (size < sizeof(t_malloc_chunk) || size & 7)
				{
					if (g_malloc_data.debug_var & MALLOC_ERROR_ABORT
						|| g_malloc_data.debug_var & MALLOC_CORRUPTION_ABORT)
						abort();
//					write(1, "SHIT\n", 5);
					return (NULL);
				}
				chunk = (void *)chunk + size;
//				write(1, "#\n", 2);
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
		if (chunk + 1 == ptr)
			return (chunk);
		if ((chunk = chunk->next) == g_malloc_data.large)
			break ;
	}
	return (NULL);
}
