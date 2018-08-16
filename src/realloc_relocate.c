/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_relocate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 14:41:55 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/16 14:51:41 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

void	*realloc_relocate(t_malloc_chunk *chunk, size_t size, void *data,
						  void (*free_chunk)(t_malloc_chunk *))
{
	void	*ptr;

	if (g_malloc_data.debug_var & MALLOC_VERBOSE)
		malloc_verbose("realloc", "relocate data", NULL, 0);
	ptr = malloc(size);
	if (ptr == NULL)
		return (NULL);
	ft_memcpy(data, ptr, (size < chunk->size ? size : chunk->size));
	(*free_chunk)(chunk);
	return (ptr);
}
