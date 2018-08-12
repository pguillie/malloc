/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_top.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:09:15 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/12 16:58:33 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

static t_malloc_arena	*ft_malloc_arena(size_t size)
{
	t_malloc_arena	*arena;
	size_t			align;
	size_t			length;

	align = getpagesize() - 1;
	if (size <= 64 + 2 * sizeof(size_t) + MALLOC_ALIGN & ~MALLOC_ALIGN)
		length = 100 * (2 * sizeof(size_t) + 64) + align & ~align;
	else
		length = 100 * (2 * sizeof(size_t) + 4096) + align & ~align;
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

static t_malloc_arena	*ft_malloc_get_arena(t_malloc_arena **first_arena,
											size_t size)
{
	t_malloc_arena	*arena;

	if (*first_arena)
	{
		arena = *first_arena;
		while (arena->top->size < size + sizeof(t_malloc_chunk))
		{
			if (arena->next == NULL)
			{
				arena->next = ft_malloc_arena(size);
				if (arena->next = NULL)
					return (NULL);
			}
			arena = arena->next;
		}
	}
	else
	{
		*first_arena = ft_malloc_arena(size);
		arena = *first_arena;
	}
	return (arena);
}

void					*ft_malloc_top(t_malloc_arena *first_arena, size_t size)
{
	t_malloc_arena	*arena;
	t_malloc_chunk	*chunk;
	size_t			align;

	size = size + 2 * sizeof(t_size) + MALLOC_ALIGN & ~MALLOC_ALIGN;
	arena = ft_malloc_get_arena(&first_arena, size);
	if (arena == NULL)
		return (NULL);
	chunk = arena->top;
	arena->top += size;
	arena->top->prev_size = size;
	arena->top->size = chunk->size - size;
	chunk->size = size;
	return ((void *)chunk + 2 * sizeof(size_t));
}
