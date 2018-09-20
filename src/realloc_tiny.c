/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_tiny.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 14:19:45 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/20 22:14:17 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

void	*realloc_tiny(t_malloc_chunk *chunk, size_t size)
{
	if (g_malloc_data.debug & MALLOC_FULL_VERBOSE)
		malloc_verbose("tiny chunk %p of size %n\n", chunk, chunk->size);
	if (size + 2 * sizeof(size_t) <= chunk->size)
		return ((void *)chunk + 2 * sizeof(size_t));
	return (realloc_relocate(chunk, size, (void *)chunk + 2 * sizeof(size_t),
				&free_tiny));
}
