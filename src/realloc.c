/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 18:58:04 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/16 15:06:27 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

void		*realloc(void *ptr, size_t size)
{
	t_malloc_chunk	*chunk;
	void			*ret;

	if (!(g_malloc_data.debug_var & MALLOC_INIT))
		malloc_init();
	if (g_malloc_data.debug_var & MALLOC_VERBOSE)
		malloc_verbose("realloc", NULL, ptr, size);
	if (ptr == NULL)
		return (malloc(size));
	ret = NULL;
	if (size == 0)
		free(ptr);
	else if ((chunk = get_tiny_chunk(ptr)))
		ret = realloc_tiny(chunk, size);
	else if ((chunk = get_small_chunk(ptr)))
		ret = realloc_small(chunk, size);
	else if ((chunk = get_large_chunk(ptr)))
		ret = realloc_large(chunk, size);
	if (ret == NULL && g_malloc_data.debug_var & MALLOC_ERROR_ABORT)
		abort();
	return (ret);
}
