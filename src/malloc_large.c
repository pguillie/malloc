/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_large.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 12:55:42 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/16 12:44:33 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

void	*malloc_large(size_t size)
{
	t_malloc_chunk	*large;
	size_t			align;
	size_t			length;

	align = getpagesize() - 1;
	length = (size + sizeof(t_malloc_chunk) + align) & ~align;
	if (g_malloc_data.debug_var & MALLOC_VERBOSE)
		malloc_verbose("malloc_large", "chunk size:", NULL, length);
	large = (t_malloc_chunk *)mmap(NULL, length, PROT_READ | PROT_WRITE,
								   MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (large == MAP_FAILED)
		return (NULL);
	large->size = length;
	if (g_malloc_data.large)
	{
		if (g_malloc_data.debug_var & MALLOC_VERBOSE)
			malloc_verbose("malloc_large", "add chunk:", large, large->size);
		large->prev = (g_malloc_data.large)->prev;
		large->next = g_malloc_data.large;
		(g_malloc_data.large)->prev = large;
		large->prev->next = large;
	}
	else
	{
		if (g_malloc_data.debug_var & MALLOC_VERBOSE)
			malloc_verbose("malloc_large", "first large chunk:", large, large->size);
		large->prev = large;
		large->next = large;
		g_malloc_data.large = large;
	}
	return ((void *)(large + 1));//sizeof(t_malloc_chunk));
}
