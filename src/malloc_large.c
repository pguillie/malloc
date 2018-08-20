/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_large.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 12:55:42 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/20 17:11:03 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

static void	malloc_large_add(t_malloc_chunk *chunk)
{
	if (g_malloc_data.large)
	{
		if (g_malloc_data.debug & MALLOC_VERBOSE)
			malloc_verbose("malloc_large", "add chunk:", chunk, chunk->size);
		chunk->prev = (g_malloc_data.large)->prev;
		chunk->next = g_malloc_data.large;
		(g_malloc_data.large)->prev = chunk;
		chunk->prev->next = chunk;
	}
	else
	{
		if (g_malloc_data.debug & MALLOC_VERBOSE)
			malloc_verbose("malloc_large", "first large chunk:",
					chunk, chunk->size);
		chunk->prev = chunk;
		chunk->next = chunk;
		g_malloc_data.large = chunk;
	}
}

void		*malloc_large(size_t size)
{
	t_malloc_chunk	*large;
	size_t			align;
	size_t			length;

	align = getpagesize() - 1;
	length = (size + sizeof(t_malloc_chunk) + align) & ~align;
	if (g_malloc_data.debug & MALLOC_VERBOSE)
		malloc_verbose("malloc_large", "chunk size:", NULL, length);
	large = (t_malloc_chunk *)mmap(NULL, length, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (large == MAP_FAILED)
		return (NULL);
	large->size = length;
	malloc_large_add(large);
	return ((void *)(large + 1));
}
