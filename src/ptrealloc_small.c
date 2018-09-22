/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptrealloc_small.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 14:32:06 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/22 13:24:18 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

void	*ptrealloc_small(t_malloc_chunk *chunk, size_t size)
{
	if (g_malloc_data.debug & MALLOC_FULL_VERBOSE)
		malloc_verbose("small chunk %p of size %n\n", chunk, chunk->size);
	if (size > MALLOC_TINY_SIZE && size + 2 * sizeof(size_t) <= chunk->size)
		return ((void *)chunk + 2 * sizeof(size_t));
	return (ptrealloc_relocate(chunk, size, (void *)chunk + 2 * sizeof(size_t),
				&ptfree_small));
}
