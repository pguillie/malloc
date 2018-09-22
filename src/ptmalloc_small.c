/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptmalloc_small.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 17:32:04 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/22 13:22:40 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

static void	ptmalloc_small_split(t_malloc_chunk *chunk, size_t size)
{
	t_malloc_chunk	*split;

	split = (t_malloc_chunk *)((void *)chunk + size);
	split->size = (chunk->size - size) | MALLOC_FREE_CHUNK;
	chunk->size = size;
	split->prev_size = size;
	ptfree_small_insert(split);
	if (g_malloc_data.debug & MALLOC_FULL_VERBOSE)
		malloc_verbose("new splitted chunk %p of size %n\n",
				split, split->size);
}

static void	*ptmalloc_pull(t_malloc_chunk *chunk, size_t size)
{
	chunk->size &= ~MALLOC_FREE_CHUNK;
	if (g_malloc_data.debug & MALLOC_FULL_VERBOSE)
		malloc_verbose("pull small chunk %p of size %n\n", chunk, chunk->size);
	if (chunk->size > size + 2 * sizeof(size_t) + MALLOC_TINY_SIZE)
		ptmalloc_small_split(chunk, size);
	chunk->prev->next = chunk->next;
	chunk->next->prev = chunk->prev;
	if (g_malloc_data.free[0] == chunk)
		g_malloc_data.free[0] = (chunk->next != chunk ? chunk->next : NULL);
	return ((void *)chunk + 2 * sizeof(size_t));
}

void		*ptmalloc_small(size_t size)
{
	t_malloc_chunk	*free;
	void			*ptr;

	size = (2 * sizeof(size_t) + size + 15) & ~15;
	if (g_malloc_data.debug & MALLOC_FULL_VERBOSE)
		malloc_verbose("small chunk of size %n\n", size);
	free = g_malloc_data.free[0];
	while (free)
	{
		if (free->size >= size)
		{
			ptr = ptmalloc_pull(free, size);
			if (g_malloc_data.debug & MALLOC_SCRIBLE)
			{
				if (g_malloc_data.debug & MALLOC_VERBOSE)
					malloc_verbose("fill memory with 0xaa bytes\n");
				ft_memset(ptr, 0xaa, size - 2 * sizeof(size_t));
			}
			return (ptr);
		}
		if ((free = free->next) == g_malloc_data.free[0])
			break ;
	}
	return (ptmalloc_top(&(g_malloc_data.small), size, MALLOC_SMALL_SIZE));
}
