/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptfree_tiny.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 14:09:40 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/22 12:36:34 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

void	ptfree_tiny(t_malloc_chunk *chunk)
{
	void	*ptr;
	int		i;

	if (g_malloc_data.debug & MALLOC_FULL_VERBOSE)
		malloc_verbose("tiny chunk %p of size %n\n", chunk, chunk->size);
	ptr = (void *)chunk + 2 * sizeof(size_t);
	if (chunk->size & MALLOC_FREE_CHUNK)
		abort_free("double free pointer", ptr, MALLOC_CORRUPTION_ABORT);
	if (g_malloc_data.debug & MALLOC_SCRIBLE)
	{
		if (g_malloc_data.debug & MALLOC_VERBOSE)
			malloc_verbose("fill memory with 0x55 bytes\n");
		ft_memset(ptr, 0x55, chunk->size - 2 * sizeof(size_t));
	}
	i = chunk->size / 16 - 1;
	chunk->size |= MALLOC_FREE_CHUNK;
	chunk->next = g_malloc_data.free[i];
	g_malloc_data.free[i] = chunk;
}
