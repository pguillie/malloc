/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:09:36 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/18 11:51:05 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

void		free(void *ptr)
{
	t_malloc_chunk	*chunk;

	if (!(g_malloc_data.debug_var & MALLOC_INIT))
		malloc_init();
	if (g_malloc_data.debug_var & MALLOC_VERBOSE)
		malloc_verbose("free", "pointer:", ptr, 0);
	if (ptr)
	{
		if ((chunk = get_tiny_chunk(ptr)))
			free_tiny(chunk);
		else if ((chunk = get_small_chunk(ptr)))
			free_small(chunk);
		else if ((chunk = get_large_chunk(ptr)))
			free_large(chunk);
		else
		{
			if (g_malloc_data.debug_var & MALLOC_VERBOSE)
				malloc_verbose("free", "pointer not found:", ptr, 0);
			if (g_malloc_data.debug_var & MALLOC_ERROR_ABORT)
				abort();
		}
	}
//	write(1, "END FREE\n", 9);
}
