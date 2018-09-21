/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 18:58:04 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/20 19:07:08 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

void		*realloc(void *ptr, size_t size)
{
	t_malloc_chunk	*chunk;
	void			*ret;

	if (!(g_malloc_data.debug & MALLOC_INIT))
		malloc_init();
	if (g_malloc_data.debug & MALLOC_VERBOSE)
		malloc_verbose("REALLOC pointer %p to size %n\n", ptr, size);
	if (ptr == NULL)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	ret = NULL;
	if ((chunk = get_tiny_chunk(ptr)))
		ret = realloc_tiny(chunk, size);
	else if ((chunk = get_small_chunk(ptr)))
		ret = realloc_small(chunk, size);
	else if ((chunk = get_large_chunk(ptr)))
		ret = realloc_large(chunk, size);
	if (chunk == NULL)
		abort_realloc("illegal pointer", ptr, MALLOC_CORRUPTION_ABORT);
	if (g_malloc_data.debug & MALLOC_VERBOSE)
		malloc_verbose("return pointer %p\n", ret);
	return (ret);
}
