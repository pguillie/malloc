/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptfree_small.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 14:14:41 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/25 14:28:03 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

t_malloc_chunk	*ptfree_coalesce(t_malloc_chunk *a, t_malloc_chunk *b)
{
	if (g_malloc_data.debug & MALLOC_FULL_VERBOSE)
		malloc_verbose("coalesce chunk %p of size %n"
				" with chunk %p of size %n\n",
				a, a->size, b, b->size);
	a->size += b->size;
	((t_malloc_chunk *)((void *)b + b->size))->prev_size = a->size;
	return (a);
}

t_malloc_chunk	*ptfree_test_coalesce(t_malloc_chunk *chunk)
{
	t_malloc_chunk	*c;

	c = (t_malloc_chunk *)((void *)chunk - chunk->prev_size);
	if (c->size & MALLOC_FREE_CHUNK)
	{
		malloc_small_list_remove(c);
		chunk = ptfree_coalesce(c, chunk);
	}
	c = (t_malloc_chunk *)((void *)chunk + chunk->size);
	if (c->size & MALLOC_FREE_CHUNK)
	{
		malloc_small_list_remove(c);
		chunk = ptfree_coalesce(chunk, c);
	}
	return (chunk);
}

void			ptfree_small(t_malloc_chunk *chunk)
{
	if (g_malloc_data.debug & MALLOC_FULL_VERBOSE)
		malloc_verbose("free small chunk %p of size %n\n",
				chunk, chunk->size & ~MALLOC_FREE_CHUNK);
	if (chunk->size & MALLOC_FREE_CHUNK)
		abort_free("double free pointer",
				(void *)chunk + 2 * sizeof(size_t), MALLOC_CORRUPTION_ABORT);
	if (g_malloc_data.debug & MALLOC_SCRIBLE)
	{
		if (g_malloc_data.debug & MALLOC_VERBOSE)
			malloc_verbose("fill memory with 0x55 bytes\n");
		ft_memset((void *)chunk + 2 * sizeof(size_t), 0x55,
				chunk->size - 2 * sizeof(size_t));
	}
	chunk = ptfree_test_coalesce(chunk);
	malloc_small_list_add(chunk);
}
