/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:09:36 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/14 15:32:01 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

void	free(void *ptr)
{
	t_malloc_chunk	*chunk;

	if ((chunk = get_tiny_chunk(ptr)))
		free_tiny(chunk);
	else if ((chunk = get_small_chunk(ptr)))
		free_small(chunk);
	else if ((chunk = get_large_chunk(ptr)))
		free_large(chunk);
}
