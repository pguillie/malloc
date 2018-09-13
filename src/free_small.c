/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 14:14:41 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/13 18:40:58 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

static void	free_small_set(t_malloc_chunk *chunk)
{
	if (g_malloc_data.debug & MALLOC_VERBOSE)
		malloc_verbose("free_small", "set free list", NULL, 0);
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
	if (g_malloc_data.debug & MALLOC_VERBOSE)
		malloc_verbose("free_small", "insert before chunk:", free, free->size);
	chunk->prev = free->prev;
	free->prev = chunk;
	chunk->next = free;
	chunk->prev->next = chunk;
	if (free == g_malloc_data.free[0] && chunk->size < free->size)
		g_malloc_data.free[0] = chunk;
}

void		free_small(t_malloc_chunk *chunk)
{
/* 	if (((t_malloc_chunk *)((void *)chunk + chunk->size))->prev_size) */
/* 	{ */
/* 		write(1, "->free\n", 7); */
/* 		abort(); */
/* 	} */
	if (g_malloc_data.debug & MALLOC_VERBOSE)
		malloc_verbose("free_small", "free chunk:", chunk, chunk->size);
	if (chunk->size & MALLOC_FREE_CHUNK)
	{
		if (g_malloc_data.debug & MALLOC_VERBOSE)
			malloc_verbose("free", "chunk has already been free'd:",
					chunk, chunk->size ^ MALLOC_FREE_CHUNK);
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
