/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptmalloc_small.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 17:32:04 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/25 14:28:46 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

static void	ptmalloc_split(t_malloc_chunk *chunk, size_t size)
{
	t_malloc_chunk	*split;

	split = (t_malloc_chunk *)((void *)chunk + size);
	split->size = chunk->size - size;
	split->prev_size = size;
	chunk->size = size;
	((t_malloc_chunk *)((void *)split + split->size))->prev_size =
		split->size;
	malloc_small_list_add(split);
}

static void	*ptmalloc_pull(t_malloc_chunk *chunk, size_t size)
{
	void	*ptr;

	if (g_malloc_data.debug & MALLOC_FULL_VERBOSE)
		malloc_verbose("pull small chunk %p of size %n\n",
				chunk, chunk->size & ~MALLOC_FREE_CHUNK);
	malloc_small_list_remove(chunk);
	if (chunk->size > size + 2 * sizeof(size_t) + MALLOC_TINY_SIZE)
		ptmalloc_split(chunk, size);
	ptr = (void *)chunk + 2 * sizeof(size_t);
	if (g_malloc_data.debug & MALLOC_SCRIBLE)
	{
		if (g_malloc_data.debug & MALLOC_VERBOSE)
			malloc_verbose("fill memory with 0xaa bytes\n");
		ft_memset(ptr, 0xaa, size - 2 * sizeof(size_t));
	}
	return (ptr);
}

void		*ptmalloc_small(size_t size)
{
	t_malloc_chunk	*free;

	size = (2 * sizeof(size_t) + size + 15) & ~15;
	if (g_malloc_data.debug & MALLOC_FULL_VERBOSE)
		malloc_verbose("small chunk of size %n\n", size);
	free = g_malloc_data.free[0];
	while (free)
	{
		if (free->size >= size)
			return (ptmalloc_pull(free, size));
		if ((free = free->next) == g_malloc_data.free[0])
			break ;
	}
	return (ptmalloc_top(&(g_malloc_data.small), size, MALLOC_SMALL_SIZE));
}
