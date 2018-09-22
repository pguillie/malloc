/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptmalloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:09:26 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/22 18:05:31 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*ptmalloc(size_t size)
{
	void	*ptr;

	if (size <= MALLOC_TINY_SIZE)
		ptr = ptmalloc_tiny(size);
	else if (size <= MALLOC_SMALL_SIZE)
		ptr = ptmalloc_small(size);
	else
		ptr = ptmalloc_large(size);
	if (ptr == NULL)
		abort_malloc("failed to allocate memory", MALLOC_ERROR_ABORT);
	return (ptr);
}
