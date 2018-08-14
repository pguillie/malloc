/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_top.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:09:15 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/14 17:45:30 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

static t_malloc_arena	*malloc_new_arena(size_t elem_size)
{
	t_malloc_arena	*arena;
	size_t			align;
	size_t			length;

	align = getpagesize() - 1;
	length = (100 * (2 * sizeof(size_t) + elem_size) + align) & ~align;
	arena = (t_malloc_arena *)mmap(NULL, length, PROT_READ | PROT_WRITE,
								   MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (arena == MAP_FAILED)
		return (NULL);
	arena->top = (t_malloc_chunk *)arena + sizeof(t_malloc_arena);
	arena->top->prev_size = 0;
	arena->top->size = length - sizeof(t_malloc_arena);
	arena->next = NULL;
	return (arena);	
}

static t_malloc_arena	*malloc_get_arena(t_malloc_arena **start, size_t size,
										  size_t elem_size)
{
	t_malloc_arena	*arena;

	if (*start)
	{
		arena = *start;
		while (arena->top->size < size + sizeof(t_malloc_chunk))
		{
			if (arena->next == NULL)
				return ((arena->next = malloc_new_arena(elem_size)));
			arena = arena->next;
		}
		return (arena);
	}
	return ((*start = malloc_new_arena(elem_size)));
}

void					*malloc_top(t_malloc_arena **start, size_t size,
									size_t elem_size)
{
	t_malloc_arena	*arena;
	t_malloc_chunk	*chunk;

	if ((arena = malloc_get_arena(start, size, elem_size)) == NULL)
		return (NULL);
	chunk = arena->top;
	arena->top = chunk + size;
	arena->top->prev_size = size;
	arena->top->size = chunk->size - size;
	chunk->size = size;
	return ((void *)chunk + 2 * sizeof(size_t));
}
