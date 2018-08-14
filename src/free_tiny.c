/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tiny.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 14:09:40 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/14 14:46:57 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

void	free_tiny(t_malloc_chunk *chunk)
{
	int	i;

	i = chunk->size / 8 - 3;
	chunk->next = g_malloc_data.free[i];
	g_malloc_data.free[i] = chunk;
}
