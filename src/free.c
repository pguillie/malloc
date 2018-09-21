/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:09:36 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/20 19:06:50 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

void		free(void *ptr)
{
	t_malloc_chunk	*chunk;

	if (!(g_malloc_data.debug & MALLOC_INIT))
		malloc_init();
	if (g_malloc_data.debug & MALLOC_VERBOSE)
		malloc_verbose("FREE pointer %p\n", ptr);
	if (ptr)
	{
		if ((chunk = get_tiny_chunk(ptr)))
			free_tiny(chunk);
		else if ((chunk = get_small_chunk(ptr)))
			free_small(chunk);
		else if ((chunk = get_large_chunk(ptr)))
			free_large(chunk);
		else
			abort_free("illegal pointer", ptr, MALLOC_CORRUPTION_ABORT);
	}
}
