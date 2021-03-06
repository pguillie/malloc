/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptmalloc_large.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 12:55:42 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/25 18:42:12 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

static void	ptmalloc_large_add(t_malloc_chunk *chunk)
{
	if (g_malloc_data.debug & MALLOC_FULL_VERBOSE)
		malloc_verbose("new large chunk %p of size %n\n", chunk, chunk->size);
	if (g_malloc_data.large)
	{
		chunk->prev = (g_malloc_data.large)->prev;
		chunk->next = g_malloc_data.large;
		(g_malloc_data.large)->prev = chunk;
		chunk->prev->next = chunk;
	}
	else
	{
		chunk->prev = chunk;
		chunk->next = chunk;
		g_malloc_data.large = chunk;
	}
}

void		*ptmalloc_large(size_t size)
{
	t_malloc_chunk	*large;
	size_t			align;
	size_t			length;
	void			*ptr;

	align = getpagesize() - 1;
	length = (size + sizeof(t_malloc_chunk) + align) & ~align;
	if (g_malloc_data.debug & MALLOC_FULL_VERBOSE)
		malloc_verbose("large chunk size of %n\n", length);
	large = (t_malloc_chunk *)mmap(NULL, length, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (large == MAP_FAILED)
		return (NULL);
	large->size = length;
	ptmalloc_large_add(large);
	ptr = (void *)(large + 1);
	if (g_malloc_data.debug & MALLOC_SCRIBLE)
	{
		if (g_malloc_data.debug & MALLOC_VERBOSE)
			malloc_verbose("fill memory with 0xaa bytes\n");
		ft_memset(ptr, 0xaa, length - sizeof(t_malloc_chunk));
	}
	return (ptr);
}
