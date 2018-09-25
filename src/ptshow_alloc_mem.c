/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptshow_alloc_mem.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 17:35:47 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/25 18:57:21 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

void	ptshow_alloc_mem(void)
{
	size_t	total;

	total = 0;
	total += show_alloc_tiny(g_malloc_data.tiny, 0);
	total += show_alloc_small(g_malloc_data.small, 0);
	total += show_alloc_large(g_malloc_data.large);
	show_alloc_mem_total(total);
}
