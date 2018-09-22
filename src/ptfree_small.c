/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptfree_small.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 14:14:41 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/22 13:20:29 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

static void	ptfree_small_set(t_malloc_chunk *chunk)
{
	if (g_malloc_data.debug & MALLOC_FULL_VERBOSE)
		malloc_verbose("set free list\n");
	chunk->next = chunk;
	chunk->prev = chunk;
	g_malloc_data.free[0] = chunk;
}

void		ptfree_small_insert(t_malloc_chunk *chunk)
{
	t_malloc_chunk	*free;

	free = g_malloc_data.free[0];
	while (free->size < chunk->size)
		if ((free = free->next) == g_malloc_data.free[0])
			break ;
	if (g_malloc_data.debug & MALLOC_FULL_VERBOSE)
		malloc_verbose("insert before free chunk %p of size %n\n",
				free, free->size & ~MALLOC_FREE_CHUNK);
	chunk->prev = free->prev;
	free->prev = chunk;
	chunk->next = free;
	chunk->prev->next = chunk;
	if (free == g_malloc_data.free[0] && chunk->size < free->size)
		g_malloc_data.free[0] = chunk;
}

void		ptfree_small(t_malloc_chunk *chunk)
{
	if (g_malloc_data.debug & MALLOC_FULL_VERBOSE)
		malloc_verbose("free small chunk %p of size %n\n",
				chunk, chunk->size & ~MALLOC_FREE_CHUNK);
	if (chunk->size & MALLOC_FREE_CHUNK)
		abort_free("double free pointer",
				(void *)chunk + 2 * sizeof(size_t), MALLOC_CORRUPTION_ABORT);
	if (g_malloc_data.debug & MALLOC_SCRIBLE)
	{
		if (g_malloc_data.debug & MALLOC_VERBOSE)
			malloc_verbose("fill memory with 0x55 bytes\n");
		ft_memset((void *)chunk + 2 * sizeof(size_t), 0x55,
				chunk->size - 2 * sizeof(size_t));
	}
	chunk = ptfree_coalesce(chunk);
	if (g_malloc_data.free[0])
		ptfree_small_insert(chunk);
	else
		ptfree_small_set(chunk);
}
