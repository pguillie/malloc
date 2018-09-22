/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptrealloc_large.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 14:37:51 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/22 13:24:31 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

void	*ptrealloc_large(t_malloc_chunk *chunk, size_t size)
{
	if (g_malloc_data.debug & MALLOC_FULL_VERBOSE)
		malloc_verbose("large chunk %p of size %n\n", chunk, chunk->size);
	if (size > MALLOC_SMALL_SIZE
		&& size + sizeof(t_malloc_chunk) <= chunk->size)
		return ((void *)(chunk + 1));
	return (ptrealloc_relocate(chunk, size, chunk + 1, &ptfree_large));
}
