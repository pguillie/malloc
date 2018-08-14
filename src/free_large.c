/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_large.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 15:15:32 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/14 17:41:48 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

void	free_large(t_malloc_chunk *chunk)
{
	chunk->prev->next = chunk->next;
	chunk->next->prev = chunk->prev;
	if (g_malloc_data.large == chunk)
		g_malloc_data.large = (chunk->next == chunk ? chunk->next : NULL);
	munmap((void *)chunk, chunk->size);
}
