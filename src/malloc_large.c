/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_large.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 12:55:42 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/14 17:47:11 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

void	*malloc_large(size_t size)
{
	t_malloc_chunk	*large;
	size_t			align;
	size_t			length;

	align = getpagesize() - 1;
	length = size + sizeof(t_malloc_chunk) + align & ~align;
	large = (t_malloc_chunk *)mmap(NULL, length, PROT_READ | PROT_WRITE,
								   MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (large == MAP_FAILED)
		return (NULL);
	large->size = length;
	if (g_malloc_data.large)
	{
		large->prev = (g_malloc_data.large)->prev;
		large->next = g_malloc_data.large;
		(g_malloc_data.large)->prev = large;
		large->prev->next = large;
	}
	else
	{
		large->prev = large;
		large->next = large;
		g_malloc_data.large = large;
	}
	return ((void *)large + sizeof(t_malloc_chunk));
}
