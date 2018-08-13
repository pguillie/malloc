/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 18:58:04 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/13 16:06:05 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*ft_realloc(void *ptr, size_t size)
{
	t_malloc_chunk	*chunk;
	void			*new;

	if ((chunk = malloc_get_tiny(ptr)))
	{
		if (chunk->size - (size < 16 ? 16 : size) < 8)
			return (ptr);
		if ((new = malloc(size)) == NULL)
			return (NULL);
		ft_memcpy(ptr, new, (size < chunk->size ? size : chunk->size));
		ft_free_tiny(chunk);
		return (new);
	}
	if ((chunk = malloc_get_small(ptr)))
	{
		if (chunk->size
	}
}
