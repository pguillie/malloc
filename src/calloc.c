/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 12:57:37 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/22 13:18:00 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;
pthread_mutex_t	g_mutex;

void	*calloc(size_t nelem, size_t elsize)
{
	void	*ptr;

	pthread_mutex_lock(&g_mutex);
	if (!(g_malloc_data.debug & MALLOC_INIT))
		malloc_init();
	if (g_malloc_data.debug & MALLOC_VERBOSE)
		malloc_verbose("CALLOC of %n objects of size %n\n", nelem, elsize);
	ptr = ptcalloc(nelem, elsize);
	if (g_malloc_data.debug & MALLOC_VERBOSE)
		malloc_verbose("return pointer %p\n", ptr);
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}
