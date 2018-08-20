/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tiny.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 14:09:40 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/20 17:08:43 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

void	free_tiny(t_malloc_chunk *chunk)
{
	int	i;

	if (g_malloc_data.debug & MALLOC_VERBOSE)
		malloc_verbose("free_tiny", "free chunk:", chunk, chunk->size);
	if (chunk->size & MALLOC_FREE_CHUNK)
	{
		if (g_malloc_data.debug & MALLOC_VERBOSE)
			malloc_verbose("free", "chunk already been free'd:",
					chunk, chunk->size ^ MALLOC_FREE_CHUNK);
		if (g_malloc_data.debug & MALLOC_CORRUPTION_ABORT
				|| g_malloc_data.debug & MALLOC_ERROR_ABORT)
			abort();
		return ;
	}
	i = chunk->size / 16 - 1;
	chunk->size |= MALLOC_FREE_CHUNK;
	chunk->next = g_malloc_data.free[i];
	g_malloc_data.free[i] = chunk;
}
