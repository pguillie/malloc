/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptfree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:09:36 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/22 18:06:50 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		ptfree(void *ptr)
{
	t_malloc_chunk	*chunk;

	if (ptr)
	{
		if ((chunk = get_tiny_chunk(ptr)))
			ptfree_tiny(chunk);
		else if ((chunk = get_small_chunk(ptr)))
			ptfree_small(chunk);
		else if ((chunk = get_large_chunk(ptr)))
			ptfree_large(chunk);
		else
			abort_free("illegal pointer", ptr, MALLOC_CORRUPTION_ABORT);
	}
}
