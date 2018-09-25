/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 14:40:52 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/25 17:58:52 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;
pthread_mutex_t	g_mutex;

void	show_alloc_mem(void)
{
	pthread_mutex_lock(&g_mutex);
	ptshow_alloc_mem();
	pthread_mutex_unlock(&g_mutex);
}
