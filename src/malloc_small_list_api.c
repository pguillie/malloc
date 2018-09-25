/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_small_list_api.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 11:09:17 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/25 12:16:39 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

void	malloc_small_list_add(t_malloc_chunk *chunk)
{
	t_malloc_chunk	*free;

	free = g_malloc_data.free[0];
	if (free == NULL)
	{
		chunk->prev = chunk;
		chunk->next = chunk;
		g_malloc_data.free[0] = chunk;
	}
	else
	{
		while (free->size < chunk->size)
		{
			free = free->next;
			if (free == g_malloc_data.free[0])
				break ;
		}
		chunk->prev = free->prev;
		chunk->next = free;
		chunk->prev->next = chunk;
		free->prev = chunk;
	}
	chunk->size |= MALLOC_FREE_CHUNK;
}

void	malloc_small_list_remove(t_malloc_chunk *chunk)
{
	chunk->prev->next = chunk->next;
	chunk->next->prev = chunk->prev;
	if (g_malloc_data.free[0] == chunk)
		g_malloc_data.free[0] = (chunk != chunk->next ? chunk->next : NULL);
	chunk->size &= ~MALLOC_FREE_CHUNK;
}
