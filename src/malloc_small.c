/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_small.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 17:32:04 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/13 17:47:26 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	*g_malloc_data;

t_malloc_arena	*malloc_new_arena(size_t size_max)
{
	t_malloc_arena	*arena;
	size_t			align;
	size_t			length;

	align = getpagesize() - 1;
	length = 100 * (2 * sizeof(size_t) + size_max) + align & ~align;
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

void			*malloc_small_arena(size_t size)
{
	t_malloc_arena	*arena;

	if (g_malloc_data.small)
	{
		arena = g_malloc_data.small;
		while (1)
		{
			if (size + sizeof(t_malloc_chunk) < arena->top->chunk)
				return (arena);
			if (arena->next = NULL)
				return ((arena->next = malloc_new_arena(4096)));
			arena = arena->next;
		}
	}
	return ((g_malloc_data.small = malloc_new_arena(4096)));
}

void			*malloc_small_top(size_t size)
{
	t_malloc_arena	*arena;
	t_malloc_chunk	*chunk;

	if ((arena = malloc_small_arena(size)) == NULL)
		return (NULL);
	chunk = arena->top;
	arena->top = chunk + size;
	arena->top->prev_size = size;
	arena->top->size = chunk->size - size;
	chunk->size = size;
	return ((void *)chunk + 2 * sizeof(size_t));
}

void			*malloc_pull(t_malloc_chunk *chunk)
{
	//pull chunk out of free list
	//remove free_bit
	//check `uncoallesce`
}

void			*malloc_small(size_t size)
{
	t_malloc_chunk	*free;

	size = 2 * sizeof(size_t) + size + 15 & ~15;
	free = g_malloc_data.free[0];
	while (free)
	{
		if (free->size >= size)
			return (malloc_pull(free));
		if ((free = free->next) == g_malloc_data.free[0])
			break ;
	}
	return (malloc_tiny_top(size));
}
