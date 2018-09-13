/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_coalesce.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 17:14:38 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/13 18:30:29 by pguillie         ###   ########.fr       */
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
		c->size &= ~MALLOC_FREE_CHUNK;
		((t_malloc_chunk *)((void *)c + c->size))->prev_size += chunk->size;
		if (((t_malloc_chunk *)((void *)c + c->size))->prev_size & MALLOC_FREE_CHUNK)
		{
			write(1, "->coalN\n", 8);
			abort();
		}
		chunk->size += c->size;
		free_remove(c);
	}
}

t_malloc_chunk	*free_coalesce(t_malloc_chunk *chunk)
{
	t_malloc_chunk	*c;

	if (((t_malloc_chunk *)((void *)chunk + chunk->size))->prev_size)
	{
		write(1, "->coalP1\n", 9);
		abort();
	}
	free_coalesce_next(chunk);
	if (((t_malloc_chunk *)((void *)chunk + chunk->size))->prev_size)
	{
		write(1, "->coalP2\n", 9);
		abort();
	}
	c = (t_malloc_chunk *)((void *)chunk - chunk->prev_size);
	if (c->size & MALLOC_FREE_CHUNK)
	{
		if (g_malloc_data.debug & MALLOC_VERBOSE)
			malloc_verbose("free_small", "coallescing with prev chunk:",
					c, c->size);
		c->size &= ~MALLOC_FREE_CHUNK;
		((t_malloc_chunk *)((void *)chunk + chunk->size))->prev_size +=
			c->size ^ MALLOC_FREE_CHUNK;
		if (((t_malloc_chunk *)((void *)chunk + chunk->size))->prev_size)
		{
			write(1, "->coalPA\n", 9);
			abort();
		}
		c->size += chunk->size;
		chunk = c;
		free_remove(c);
	}
	chunk->size |= MALLOC_FREE_CHUNK;
	return (chunk);
}
