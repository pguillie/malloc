/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_coalesce.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 19:08:48 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/12 19:08:49 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			ft_free_rm(t_malloc_chunk *free)
{
	free->size &= ~MALLOC_FREE_CHUNK;
	if (free == g_malloc_data.free[7])
	{
		if (free == free->next)
		{
			g_malloc_data.free[7] = NULL;
			return ;
		}
		else
			g_malloc_data.free[7] = free->next;
	}
	free->prev->next = free->next;
	free->next->prev = free->prev;
}

t_malloc_chunk	*ft_free_coalesce(t_malloc_chunk *chunk)
{
	t_malloc_chunk	*free;

	free = chunk + chunk->size;
	if (free->size & MALLOC_FREE_CHUNK)
	{
		(free + (free->size ^ MALLOC_FREE_CHUNK))->prev_size += chunk->size;
		chunk->size += free->size;
		ft_free_rm(free);
	}
	free = chunk - chunk->prev_size;
	if (free->size & MALLOC_FREE_CHUNK)
	{
		free->size += chunk->size;
		(chunk + chunk->size)->prev_size += chunk->size;
		chunk = free;
		ft_free_rm(free);
	}
	return (chunk);
}
