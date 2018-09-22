/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 12:34:00 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/22 13:23:31 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;
pthread_mutex_t	g_mutex;

void	*realloc(void *ptr, size_t size)
{
	void	*ret;

	pthread_mutex_lock(&g_mutex);
	if (!(g_malloc_data.debug & MALLOC_INIT))
		malloc_init();
	if (g_malloc_data.debug & MALLOC_VERBOSE)
		malloc_verbose("REALLOC pointer %p to size %n\n", ptr, size);
	ret = ptrealloc(ptr, size);
	if (g_malloc_data.debug & MALLOC_VERBOSE)
		malloc_verbose("return pointer %p\n", ret);
	pthread_mutex_unlock(&g_mutex);
	return (ret);
}
