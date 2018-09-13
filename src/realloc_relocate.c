/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_relocate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 14:41:55 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/13 16:43:12 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

#include <string.h>
#include <stdio.h>

void	*realloc_relocate(t_malloc_chunk *chunk, size_t size, void *data,
		void (*free_chunk)(t_malloc_chunk *))
{
	void	*ptr;
	size_t	chunk_size;

	if (g_malloc_data.debug & MALLOC_VERBOSE)
		malloc_verbose("realloc", "relocate data", NULL, 0);
	ptr = malloc(size);
	if (ptr == NULL)
		return (NULL);
	chunk_size = chunk->size - ((size_t)data - (size_t)chunk);
	ft_memcpy(data, ptr, (size < chunk_size ? size : chunk_size));
	(*free_chunk)(chunk);
	return (ptr);
}
