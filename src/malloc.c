/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:09:26 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/20 19:07:00 by pguillie         ###   ########.fr       */
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
		malloc_verbose("MALLOC of size %n\n", size);
	if (size <= MALLOC_TINY_SIZE)
		ptr = malloc_tiny(size);
	else if (size <= MALLOC_SMALL_SIZE)
		ptr = malloc_small(size);
	else
		ptr = malloc_large(size);
	if (ptr == NULL)
		abort_malloc("failed to allocate memory", MALLOC_ERROR_ABORT);
	if (g_malloc_data.debug & MALLOC_VERBOSE)
		malloc_verbose("return pointer %p\n", ptr);
	return (ptr);
}
