/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 14:14:41 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/20 22:15:16 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

static void	free_small_set(t_malloc_chunk *chunk)
{
	if (g_malloc_data.debug & MALLOC_FULL_VERBOSE)
		malloc_verbose("set free list\n");
	chunk->next = chunk;
	chunk->prev = chunk;
	g_malloc_data.free[0] = chunk;
}

void		free_small_insert(t_malloc_chunk *chunk)
{
	t_malloc_chunk	*free;

	free = g_malloc_data.free[0];
	while (free->size < chunk->size)
		if ((free = free->next) == g_malloc_data.free[0])
			break ;
	if (g_malloc_data.debug & MALLOC_FULL_VERBOSE)
		malloc_verbose("insert before chunk %p of size %n\n", free, free->size);
	chunk->prev = free->prev;
	free->prev = chunk;
	chunk->next = free;
	chunk->prev->next = chunk;
	if (free == g_malloc_data.free[0] && chunk->size < free->size)
		g_malloc_data.free[0] = chunk;
}

void		free_small(t_malloc_chunk *chunk)
{
	if (g_malloc_data.debug & MALLOC_FULL_VERBOSE)
		malloc_verbose("free small chunk %p of size %n\n", chunk, chunk->size);
	if (chunk->size & MALLOC_FREE_CHUNK)
	{
		malloc_verbose("WARNING free: pointer already been free'd\n",
					   (void *)chunk + 2 * sizeof(size_t));
		if (g_malloc_data.debug & MALLOC_CORRUPTION_ABORT
				|| g_malloc_data.debug & MALLOC_ERROR_ABORT)
			abort();
		return ;
	}
	chunk = free_coalesce(chunk);
	if (g_malloc_data.free[0])
		free_small_insert(chunk);
	else
		free_small_set(chunk);
}
