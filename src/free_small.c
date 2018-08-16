/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 14:14:41 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/16 17:13:39 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

static void				free_remove(t_malloc_chunk *chunk)
{
	write(1, "rm…", 3);
	chunk->prev->next = chunk->next;
	chunk->next->prev = chunk->prev;
///
	if (g_malloc_data.free[0] == chunk)
	{
		g_malloc_data.free[0] = (chunk->next != chunk ? chunk->next : NULL);
		malloc_verbose("deb", "new free small 2", g_malloc_data.free[0],
					   (g_malloc_data.free[0])->size);
	}
	write(1, "done\n", 5);
}

static t_malloc_chunk	*free_coalesce(t_malloc_chunk *chunk)
{
	t_malloc_chunk	*c;

	write(1, "coallesce\n", 10);
	c = (t_malloc_chunk *)((void *)chunk + chunk->size);
	if (c->size & MALLOC_FREE_CHUNK)
	{
		if (g_malloc_data.debug_var & MALLOC_VERBOSE)
			malloc_verbose("free_small",
						   "coallescing with next chunk:", c, c->size);
		(c + c->size)->prev_size += chunk->size;
		chunk->size += c->size;
		free_remove(c);
	}
	c = (t_malloc_chunk *)((void *)chunk - chunk->prev_size);
	if (c->size & MALLOC_FREE_CHUNK)
	{
		if (g_malloc_data.debug_var & MALLOC_VERBOSE)
			malloc_verbose("free_small",
						   "coallescing with previous chunk:", c, c->size);
		(chunk + chunk->size)->prev_size += c->size ^ MALLOC_FREE_CHUNK;
		c->size += chunk->size;
		chunk = c;
		free_remove(c);
	}
	return (chunk);
}

static void				free_small_insert(t_malloc_chunk *chunk)
{
	t_malloc_chunk	*free;

	write(1, "insert\n", 7);
	free = g_malloc_data.free[0];
	while (free->size < chunk->size)
		if ((free = free->next) == g_malloc_data.free[0])
			break ;
	if (g_malloc_data.debug_var & MALLOC_VERBOSE)
		malloc_verbose("free_small", "insert before chunk:", free, free->size);
	chunk->prev = free->prev;
	free->prev = chunk;
	chunk->next = free;
	chunk->prev->next = chunk;
}

static void				free_small_set(t_malloc_chunk *chunk)
{
	if (g_malloc_data.debug_var & MALLOC_VERBOSE)
		malloc_verbose("free_small", "set free list", NULL, 0);
	chunk->next = chunk;
	chunk->prev = chunk;
///
	g_malloc_data.free[0] = chunk;
	malloc_verbose("deb", "new free small 3", g_malloc_data.free[0],
				   (g_malloc_data.free[0])->size);
}

void					free_small(t_malloc_chunk *chunk)
{
	if (g_malloc_data.debug_var & MALLOC_VERBOSE)
		malloc_verbose("free_small", "free chunk:", chunk, chunk->size);
	chunk = free_coalesce(chunk);
	if (g_malloc_data.free[0])
		free_small_insert(chunk);
	else
		free_small_set(chunk);
	write(1, "end free\n", 9);
}
