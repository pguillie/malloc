/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptrealloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 18:58:04 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/22 18:05:23 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*ptrealloc(void *ptr, size_t size)
{
	t_malloc_chunk	*chunk;
	void			*ret;

	if (ptr == NULL)
		return (ptmalloc(size));
	if (size == 0)
	{
		ptfree(ptr);
		return (NULL);
	}
	if ((chunk = get_tiny_chunk(ptr)))
		ret = ptrealloc_tiny(chunk, size);
	else if ((chunk = get_small_chunk(ptr)))
		ret = ptrealloc_small(chunk, size);
	else if ((chunk = get_large_chunk(ptr)))
		ret = ptrealloc_large(chunk, size);
	else
	{
		abort_realloc("illegal pointer", ptr, MALLOC_CORRUPTION_ABORT);
		return (NULL);
	}
	return (ret);
}
