/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_relocate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 14:41:55 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/20 22:14:56 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

void	*realloc_relocate(t_malloc_chunk *chunk, size_t size, void *data,
		void (*free_chunk)(t_malloc_chunk *))
{
	void	*ptr;
	size_t	chunk_size;
	size_t	n;

	ptr = malloc(size);
	if (ptr == NULL)
		return (NULL);
	chunk_size = chunk->size - ((size_t)data - (size_t)chunk);
	n = (size < chunk_size ? size : chunk->size);
	if (g_malloc_data.debug & MALLOC_FULL_VERBOSE)
		malloc_verbose("relocate %n bytes from %p to %p\n", n, data, ptr);
	ft_memcpy(ptr, data, n);
	(*free_chunk)(chunk);
	return (ptr);
}
