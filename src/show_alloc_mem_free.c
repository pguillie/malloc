/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_free.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 17:23:50 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/25 17:58:45 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;
pthread_mutex_t	g_mutex;

void	show_alloc_mem_free(void)
{
	pthread_mutex_lock(&g_mutex);
	ptshow_alloc_mem_free();
	pthread_mutex_unlock(&g_mutex);
}
