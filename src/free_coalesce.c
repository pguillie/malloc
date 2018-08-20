/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_coalesce.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 17:14:38 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/20 17:35:58 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		free_remove(t_malloc_chunk *chunk)
{
	chunk->prev->next = chunk->next;
	chunk->next->prev = chunk->prev;
	if (g_malloc_data.free[0] == chunk)
		g_malloc_data.free[0] = (chunk->next != chunk ? chunk->next : NULL);
}

static void		free_coalesce_next(t_malloc_chunk *chunk)
{
	t_malloc_chunk	*c;

	c = (t_malloc_chunk *)((void *)chunk + chunk->size);
	if (c->size & MALLOC_FREE_CHUNK)
	{
		if (g_malloc_data.debug & MALLOC_VERBOSE)
			malloc_verbose("free_small", "coallescing with next chunk:",
					c, c->size);
		c->size ^= MALLOC_FREE_CHUNK;
		((t_malloc_chunk *)((void *)c + c->size))->prev_size += chunk->size;
		chunk->size += c->size;
		free_remove(c);
	}
}

t_malloc_chunk	*free_coalesce(t_malloc_chunk *chunk)
{
	t_malloc_chunk	*c;

	free_coalesce_next(chunk);
	c = (t_malloc_chunk *)((void *)chunk - chunk->prev_size);
	if (c->size & MALLOC_FREE_CHUNK)
	{
		if (g_malloc_data.debug & MALLOC_VERBOSE)
			malloc_verbose("free_small", "coallescing with prev chunk:",
					c, c->size);
		c->size ^= MALLOC_FREE_CHUNK;
		((t_malloc_chunk *)((void *)chunk + chunk->size))->prev_size +=
			c->size ^ MALLOC_FREE_CHUNK;
		c->size += chunk->size;
		chunk = c;
		free_remove(c);
	}
	chunk->size |= MALLOC_FREE_CHUNK;
	return (chunk);
}
