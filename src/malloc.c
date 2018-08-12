/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:09:26 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/12 18:55:19 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

static void	*ft_malloc_tiny(size_t size)
{
	void	*ptr;
	int		index;

	if (size < 2 * sizeof(void *))
		size = 2 * sizeof(void *);
	index = (size - sizeof(void *) - 1) / sizeof(void *);
	if (g_malloc_data.free[index])
	{
		ptr = (void *)(g_malloc_data.free[index]) + 2 * sizeof(size_t);
		g_malloc_data.free[index] = (g_malloc_data.free[index])->next;
		return (ptr);
	}
	return (ft_malloc_top(size));
}

static void	*ft_malloc_small(size_t size)
{
	t_malloc_chunk	*small;

	small = g_malloc_data.free[7];
	while (small)
	{
		if (small->size >= size + 2 * sizeof(size_t))
		{
			ft_free_rm(small);
			return ((void *)small + 2 * sizeof(size_t));			
		}
		small = small->next;
		if (small == g_malloc_data.free[7])
			break;
	}
	return (ft_malloc_top(size))
}

static void	*ft_malloc_large(size_t size)
{
	t_malloc_chunk	*large;
	size_t			align;
	size_t			length;

	align = getpagesize() - 1;
	length = size + sizeof(t_malloc_chunk) + align & ~align;
	large = (t_malloc_chunk *)mmap(NULL, length, PROT_READ | PROT_WRITE,
								   MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (large == MAP_FAILED)
		return (NULL);
//	large->prev_size = size;							/* usefull? */
	large->size = length;
	if (g_malloc_data.large)
	{
		large->prev = (g_malloc_data.large)->prev;
		large->next = g_malloc_data.large;
		(g_malloc_data.large)->prev = large;
		large->prev->next = large;
	}
	else
	{
		large->prev = large;
		large->next = large;
		g_malloc_data = large;
	}		
	return ((void *)large + sizeof(t_malloc_chunk));
}

void		*ft_malloc(size_t size)
{
	void	*ptr;

	if (size <= 64)
		ptr = ft_malloc_tiny(size);
	else if (size <= 4096)
		ptr = ft_malloc_small(size);
	else
		ptr = ft_malloc_large(size);
	return (ptr);
}
