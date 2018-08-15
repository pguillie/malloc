/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_top.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:09:15 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/15 18:13:51 by pguillie         ###   ########.fr       */
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
	if (g_malloc_data.debug_var & MALLOC_VERBOSE)
		malloc_verbose("malloc_top", "create new arena of size:", NULL, length);
	arena = (t_malloc_arena *)mmap(NULL, length, PROT_READ | PROT_WRITE,
								   MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (arena == MAP_FAILED)
		return (NULL);
	arena->top = (t_malloc_chunk *)(arena + 1);//sizeof(t_malloc_arena);
	arena->top->prev_size = 0;
	arena->top->size = length - sizeof(t_malloc_arena);
	arena->next = NULL;
/* 	malloc_verbose("test1", NULL, (void *)arena + arena->top->size + sizeof(t_malloc_arena), 0); */
/* 	malloc_verbose("test2", NULL, (void *)arena->top + arena->top->size, 0); */
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
	if (g_malloc_data.debug_var & MALLOC_VERBOSE)
	{
		malloc_verbose("malloc_top", "arena:", arena, 0);
		malloc_verbose("malloc_top", "top chunk:", arena->top, arena->top->size);
	}
	chunk = arena->top;
	arena->top = chunk + size;
	arena->top->prev_size = size;
	arena->top->size = chunk->size - size;
	chunk->size = size;
//	write(1, "OK\n", 3);
	return ((void *)chunk + 2 * sizeof(size_t));
}
