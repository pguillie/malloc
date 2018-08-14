/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_tiny.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 16:13:35 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/14 17:43:37 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

void	*malloc_tiny(size_t size)
{
	void			*ptr;
	int				i;

	size = (2 * sizeof(size_t)
			+ (size <= 2 * sizeof(void *) ? 2 * sizeof(void *) : size) + 7) & ~7;
	i = size / 8 - 3;
	if (g_malloc_data.free[i])
	{
		ptr = (void *)(g_malloc_data.free[i]) + 2 * sizeof(size_t);
		g_malloc_data.free[i] = (g_malloc_data.free[i])->next;
		return (ptr);
	}
	return (malloc_top(&(g_malloc_data.tiny), size, 64));
}
