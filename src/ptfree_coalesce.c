/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptfree_coalesce.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 17:14:38 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/22 19:52:18 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void				ptfree_remove(t_malloc_chunk *chunk)
{
	chunk->prev->next = chunk->next;
	chunk->next->prev = chunk->prev;
	if (g_malloc_data.free[0] == chunk)
		g_malloc_data.free[0] = (chunk->next != chunk ? chunk->next : NULL);
}

static t_malloc_chunk	*ptfree_coalesce_next(t_malloc_chunk *chunk)
{
	t_malloc_chunk	*next;

	next = (t_malloc_chunk *)((void *)chunk + chunk->size);
	if (next->size & MALLOC_FREE_CHUNK)
	{
		next->size &= ~MALLOC_FREE_CHUNK;
		if (g_malloc_data.debug & MALLOC_FULL_VERBOSE)
			malloc_verbose("coallesce with next chunk %p of size %n\n",
						   next, next->size);
		((t_malloc_chunk *)((void *)next + next->size))->prev_size +=
			chunk->size;
		chunk->size += next->size;
		ptfree_remove(next);
	}
	return (chunk);
}

static t_malloc_chunk	*ptfree_coalesce_prev(t_malloc_chunk *chunk)
{
	t_malloc_chunk	*prev;

	prev = (t_malloc_chunk *)((void *)chunk - chunk->prev_size);
	if (prev->size & MALLOC_FREE_CHUNK)
	{
		prev->size &= ~MALLOC_FREE_CHUNK;
		if (g_malloc_data.debug & MALLOC_FULL_VERBOSE)
			malloc_verbose("coallesce with prev chunk %p of size %n\n",
						   prev, prev->size);
		((t_malloc_chunk *)((void *)chunk + chunk->size))->prev_size +=
			prev->size;
		prev->size += chunk->size;
		chunk = prev;
		ptfree_remove(prev);
	}
	return (chunk);
}

t_malloc_chunk			*ptfree_coalesce(t_malloc_chunk *chunk)
{
	ptfree_coalesce_next(chunk);
	ptfree_coalesce_prev(chunk);
	chunk->size |= MALLOC_FREE_CHUNK;
	return (chunk);
}

// BACKUP
/* 	t_malloc_chunk	*c; */

/* 	c = (t_malloc_chunk *)((void *)chunk + chunk->size); */
/* 	if (c->size & MALLOC_FREE_CHUNK) */
/* 	{ */
/* 		if (g_malloc_data.debug & MALLOC_FULL_VERBOSE) */
/* 			malloc_verbose("coallescing with next chunk %p of size %n\n", */
/* 					c, c->size); */
/* 		c->size &= ~MALLOC_FREE_CHUNK; */
/* 		((t_malloc_chunk *)((void *)c + c->size))->prev_size += chunk->size; */
/* 		chunk->size += c->size; */
/* 		free_remove(c); */
/* 	} */

/* 	c = (t_malloc_chunk *)((void *)chunk - chunk->prev_size); */
/* 	if (c->size & MALLOC_FREE_CHUNK) */
/* 	{ */
/* 		if (g_malloc_data.debug & MALLOC_FULL_VERBOSE) */
/* 			malloc_verbose("coallescing with previous chunk %p of size %n\n", */
/* 					c, c->size); */
/* 		c->size &= ~MALLOC_FREE_CHUNK; */
/* 		((t_malloc_chunk *)((void *)chunk + chunk->size))->prev_size += */
/* 			c->size & ~MALLOC_FREE_CHUNK; */
/* 		c->size += chunk->size; */
/* 		chunk = c; */
/* 		free_remove(c); */
/* 	} */
/* 	chunk->size |= MALLOC_FREE_CHUNK; */
/* 	return (chunk); */

/* } */
