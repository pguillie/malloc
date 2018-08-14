/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 18:58:04 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/14 17:52:54 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

static void	*realloc_move(t_malloc_chunk *chunk, size_t size,
						  void (*free_chunk)(t_malloc_chunk *))
{
	void	*ptr;

	if ((ptr = malloc(size)) == NULL)
		return (NULL);
	ft_memcpy((void *)chunk + 2 * sizeof(size_t), ptr,
			  (size < chunk->size ? size : chunk->size));
	(*free_chunk)(chunk);
	return (ptr);
}

void		*realloc(void *ptr, size_t size)
{
	t_malloc_chunk	*chunk;

	if (ptr == NULL)
		return (malloc(size));
	if (size == 0)
		free(ptr);
	else if ((chunk = get_tiny_chunk(ptr)))
	{
		if (size + 2 * sizeof(size_t) <= chunk->size)
			return (ptr);
		return (realloc_move(chunk, size, &free_tiny));
	}
	else if ((chunk = get_small_chunk(ptr)))
	{
		if (size > 64 && size + 2 * sizeof(size_t) <= chunk->size)
			return (ptr);
		return (realloc_move(chunk, size, &free_small));
	}
	else if ((chunk = get_large_chunk(ptr)))
	{
		if (size > 4096 && size + sizeof(t_malloc_chunk) <= chunk->size)
			return (ptr);
		return (realloc_move(chunk, size, &free_large));
	}
	return (NULL);
}
