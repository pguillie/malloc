/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 11:45:49 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/22 13:18:56 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;
pthread_mutex_t	g_mutex;

void	free(void *ptr)
{
	pthread_mutex_lock(&g_mutex);
	if (!(g_malloc_data.debug & MALLOC_INIT))
		malloc_init();
	if (g_malloc_data.debug & MALLOC_VERBOSE)
		malloc_verbose("FREE pointer %p\n", ptr);
	ptfree(ptr);
	pthread_mutex_unlock(&g_mutex);
}
