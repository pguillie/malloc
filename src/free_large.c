/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_large.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 15:15:32 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/20 22:12:56 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

void	free_large(t_malloc_chunk *chunk)
{
	if (g_malloc_data.debug & MALLOC_FULL_VERBOSE)
		malloc_verbose("free large chunk %p of size %n\n", chunk, chunk->size);
	chunk->prev->next = chunk->next;
	chunk->next->prev = chunk->prev;
	if (g_malloc_data.large == chunk)
		g_malloc_data.large = (chunk->next != chunk ? chunk->next : NULL);
	if (munmap((void *)chunk, chunk->size) < 0)
		abort_free("failed to unmap page", (void *)chunk, MALLOC_ERROR_ABORT);
}
