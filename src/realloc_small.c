/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_small.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 14:32:06 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/16 15:06:54 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

void	*realloc_small(t_malloc_chunk *chunk, size_t size)
{
	if (g_malloc_data.debug_var & MALLOC_VERBOSE)
		malloc_verbose("realloc_tiny", "chunk:", chunk, chunk->size);
	if (size > 64 && size + 2 * sizeof(size_t) <= chunk->size)
		return ((void *)chunk + 2 * sizeof(size_t));
	return (realloc_relocate(chunk, size,
							 (void *)chunk + 2 * sizeof(size_t), &free_small));
}
