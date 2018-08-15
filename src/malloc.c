/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:09:26 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/15 17:02:44 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

void	*malloc(size_t size)
{
	void	*ptr;

	if (!(g_malloc_data.debug_var & MALLOC_INIT))
		malloc_init();
	if (g_malloc_data.debug_var & MALLOC_VERBOSE)
		malloc_verbose("malloc", "size:", NULL, size);
	if (size <= 64)
		ptr = malloc_tiny(size);
	else if (size <= 4096)
		ptr = malloc_small(size);
	else
		ptr = malloc_large(size);
	if (g_malloc_data.debug_var & MALLOC_VERBOSE)
		malloc_verbose("malloc", "pointer:", ptr, 0);
	return (ptr);
}
