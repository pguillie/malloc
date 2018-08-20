/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_tiny.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 16:13:35 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/20 17:36:31 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

void	*malloc_tiny(size_t size)
{
	void			*ptr;
	int				i;

	size = (2 * sizeof(size_t)
			+ (size <= 2 * sizeof(void *) ? 2 * sizeof(void *) : size)
			+ 15) & ~15;
	if (g_malloc_data.debug & MALLOC_VERBOSE)
		malloc_verbose("malloc_tiny", "chunk size:", NULL, size);
	i = size / 16 - 1;
	if (g_malloc_data.free[i])
	{
		if (g_malloc_data.debug & MALLOC_VERBOSE)
			malloc_verbose("malloc_tiny", "pull chunk:",
					g_malloc_data.free[i], 0);
		ptr = (void *)(g_malloc_data.free[i]) + 2 * sizeof(size_t);
		((t_malloc_chunk *)(g_malloc_data.free[i]))->size ^= MALLOC_FREE_CHUNK;
		g_malloc_data.free[i] = (t_malloc_chunk *)(g_malloc_data.free[i])->next;
		return (ptr);
	}
	return (malloc_top(&(g_malloc_data.tiny), size, MALLOC_TINY_SIZE));
}
