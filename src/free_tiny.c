/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tiny.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 14:09:40 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/20 22:11:51 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

void	free_tiny(t_malloc_chunk *chunk)
{
	int	i;

	if (g_malloc_data.debug & MALLOC_FULL_VERBOSE)
		malloc_verbose("tiny chunk %p of size %n\n", chunk, chunk->size);
	if (chunk->size & MALLOC_FREE_CHUNK)
	{
		malloc_verbose("WARNING free: pointer %p already been free'd\n",
					   (void *)chunk + 2 * sizeof(size_t));
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
