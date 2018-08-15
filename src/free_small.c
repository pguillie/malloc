/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 14:14:41 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/15 17:45:31 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

static void				free_remove(t_malloc_chunk *chunk)
{
	chunk->prev->next = chunk->next;
	chunk->next->prev = chunk->prev;
	if (g_malloc_data.free[0] == chunk)
		g_malloc_data.free[0] = (chunk->next != chunk ? chunk->next : NULL);
}

static t_malloc_chunk	*free_coalesce(t_malloc_chunk *chunk)
{
	t_malloc_chunk	*c;

	c = chunk + chunk->size;
	if (c->size & MALLOC_FREE_CHUNK)
	{
		if (g_malloc_data.debug_var & MALLOC_VERBOSE)
			malloc_verbose("free_small",
						   "coallescing with next chunk:", c, c->size);
		(c + c->size)->prev_size += chunk->size;
		chunk->size += c->size;
		free_remove(c);
	}
	c = chunk - chunk->prev_size;
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
	g_malloc_data.free[0] = chunk;
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
}
