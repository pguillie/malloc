/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_res.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 16:59:57 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/25 18:56:59 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static size_t	show_alloc_chunk(t_malloc_chunk *chunk)
{
	char	buff[128];
	size_t	size;
	size_t	i;

	i = 0;
	i += malloc_vrb_ptr(buff + i, (void *)chunk + 2 * sizeof(size_t));
	ft_memcpy(buff + i, " - ", 3);
	i += 3;
	i += malloc_vrb_ptr(buff + i,
						(void *)chunk + (chunk->size & ~MALLOC_FREE_CHUNK));
	ft_memcpy(buff + i, " : ", 3);
	i += 3;
	size = (chunk->size & ~MALLOC_FREE_CHUNK) - 2 * sizeof(size_t);
	i += malloc_vrb_nbr(buff + i, size);
	ft_memcpy(buff + i, " octets", 7);
	i += 7;
	if (chunk->size & MALLOC_FREE_CHUNK)
	{
		ft_memcpy(buff + i, " (free)", 7);
		i += 7;
	}
	buff[i++] = '\n';
	write(1, buff, i);
	return (size);
}

static size_t	show_alloc_arena(t_malloc_arena *arena, int mode)
{
	t_malloc_chunk	*chunk;
	size_t			total;

	total = 0;
	while (arena)
	{
		chunk = (t_malloc_chunk *)(arena + 1);
		while (chunk != arena->top)
		{
			if (!(chunk->size & MALLOC_FREE_CHUNK))
				total += show_alloc_chunk(chunk);
			else if (mode & SHOW_FREE)
				show_alloc_chunk(chunk);
			chunk = (t_malloc_chunk *)
				((void *)chunk + (chunk->size & ~MALLOC_FREE_CHUNK));
		}
		arena = arena->next;
	}
	return (total);
}

size_t			show_alloc_tiny(t_malloc_arena *tiny, int mode)
{
	char	buff[32];
	size_t	i;

	if (tiny == NULL)
		return (0);
	ft_memcpy(buff, "TINY : ", 7);
	i = 7;
	i += malloc_vrb_ptr(buff + i, tiny);
	buff[i++] = '\n';
	write(1, buff, i);
	return (show_alloc_arena(tiny, mode));
}

size_t			show_alloc_small(t_malloc_arena *small, int mode)
{
	char	buff[32];
	size_t	i;

	if (small == NULL)
		return (0);
	ft_memcpy(buff, "SMALL : ", 8);
	i = 8;
	i += malloc_vrb_ptr(buff + i, small);
	buff[i++] = '\n';
	write(1, buff, i);
	return (show_alloc_arena(small, mode));
}

size_t			show_alloc_large(t_malloc_chunk *large)
{
	t_malloc_chunk	*chunk;
	char			buff[64];
	size_t			total;
	size_t			i;

	if (large == NULL)
		return (0);
	ft_memcpy(buff, "LARGE : ", 8);
	i = 8;
	i += malloc_vrb_ptr(buff + i, large);
	buff[i++] = '\n';
	write(1, buff, i);
	chunk = large;
	total = 0;
	while (chunk)
	{
		total += show_alloc_chunk(chunk);
		if ((chunk = chunk->next) == large)
			break ;
	}
	return (total);
}
