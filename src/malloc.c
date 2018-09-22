/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 11:32:58 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/22 13:16:50 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;
pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;

void	*malloc(size_t size)
{
	void	*ptr;

	pthread_mutex_lock(&g_mutex);
	if (!(g_malloc_data.debug & MALLOC_INIT))
		malloc_init();
	if (g_malloc_data.debug & MALLOC_VERBOSE)
		malloc_verbose("MALLOC of size %n\n", size);
	ptr = ptmalloc(size);
	if (g_malloc_data.debug & MALLOC_VERBOSE)
		malloc_verbose("return pointer %p\n", ptr);
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}
