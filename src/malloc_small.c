/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_small.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 17:32:04 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/16 18:28:31 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

static void	*malloc_pull(t_malloc_chunk *chunk, size_t size)
{
	t_malloc_chunk	*split;

	if (g_malloc_data.debug_var & MALLOC_VERBOSE)
		malloc_verbose("malloc_small", "pull chunk:", chunk, chunk->size);
	chunk->size &= ~MALLOC_FREE_CHUNK;
	if (chunk->size > size + 2 * sizeof(size_t) + 64)
	{
		((t_malloc_chunk *)((void *)chunk + chunk->size))->prev_size -= size;
		split = (t_malloc_chunk *)((void *)chunk + size);
		split->size = (chunk->size - size) & MALLOC_FREE_CHUNK;
		chunk->size = size;
		split->prev_size = size;
		split->prev = chunk;
		split->next = chunk->next;
		chunk->next = split;
		if (g_malloc_data.debug_var & MALLOC_VERBOSE)
			malloc_verbose("malloc_small", "splitted chunk:",
						   split, split->size);
	}
	chunk->prev->next = chunk->next;
	chunk->next->prev = chunk->prev;
///
	if (g_malloc_data.free[0] == chunk)
	{
		g_malloc_data.free[0] = (chunk->next != chunk ? chunk->next : NULL);
		malloc_verbose("deb", "new free small 1", g_malloc_data.free[0],
					   (g_malloc_data.free[0])->size);
	}
	return ((void *)chunk + 2 * sizeof(size_t));
}

void		*malloc_small(size_t size)
{
	t_malloc_chunk	*free;

	size = (2 * sizeof(size_t) + size + 15) & ~15;
	if (g_malloc_data.debug_var & MALLOC_VERBOSE)
		malloc_verbose("malloc_small", "chunk size:", NULL, size);
	free = g_malloc_data.free[0];
	while (free)
	{
		malloc_verbose("deb", "small free:", free, free->size);
		if (free->size >= size)
			return (malloc_pull(free, size));
		if ((free = free->next) == g_malloc_data.free[0])
			break ;
	}
	return (malloc_top(&(g_malloc_data.small), size, 4096));
}
