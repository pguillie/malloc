/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_tiny.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 16:13:35 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/13 17:32:51 by pguillie         ###   ########.fr       */
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

void			*malloc_tiny_arena(size_t size)
{
	t_malloc_arena	*arena;

	if (g_malloc_data.tiny)
	{
		arena = g_malloc_data.tiny;
		while (1)
		{
			if (size + sizeof(t_malloc_chunk) < arena->top->chunk)
				return (arena);
			if (arena->next = NULL)
				return ((arena->next = malloc_new_arena(64)));
			arena = arena->next;
		}
	}
	return ((g_malloc_data.tiny = malloc_new_arena(64)));
}

void			*malloc_tiny_top(size_t size)
{
	t_malloc_arena	*arena;
	t_malloc_chunk	*chunk;

	if ((arena = malloc_tiny_arena(size)) == NULL)
		return (NULL);
	chunk = arena->top;
	arena->top = chunk + size;
	arena->top->prev_size = size;
	arena->top->size = chunk->size - size;
	chunk->size = size;
	return ((void *)chunk + 2 * sizeof(size_t));
}

void			*malloc_tiny(size_t size)
{
	void			*ptr;
	int				i;

	size = 2 * sizeof(size_t)
		+ (size <= 2 * sizeof(void *) ? 2 * sizeof(void *) : size + 7 & ~7);
	i = size / 8 - 1;
	if (g_malloc_data.free[i])
	{
		ptr = (void *)(g_malloc_data.free[i]) + 16;
		g_malloc_data.free[i] = (g_malloc_data.free[i])->next;
		return (ptr);
	}
	return (malloc_tiny_top(size));
}
