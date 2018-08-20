/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:09:26 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/20 13:17:55 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

void	*malloc(size_t size)
{
	void	*ptr;

	if (!(g_malloc_data.debug & MALLOC_INIT))
		malloc_init();
	if (g_malloc_data.debug & MALLOC_VERBOSE)
		malloc_verbose("malloc", "size:", NULL, size);
	if (size <= MALLOC_TINY_SIZE)
		ptr = malloc_tiny(size);
	else if (size <= MALLOC_SMALL_SIZE)
		ptr = malloc_small(size);
	else
		ptr = malloc_large(size);
	if (g_malloc_data.debug & MALLOC_VERBOSE)
		malloc_verbose("malloc", "pointer:", ptr, 0);
	return (ptr);
}
