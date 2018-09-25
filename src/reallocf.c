/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 17:46:44 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/25 17:52:24 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;
pthread_mutex_t	g_mutex;

void	*reallocf(void *ptr, size_t size)
{
	void	*ret;

	pthread_mutex_lock(&g_mutex);
	ret = ptrealloc(ptr, size);
	if (ret == NULL && size > 0)
		ptfree(ret);
	pthread_mutex_unlock(&g_mutex);
	return (ret);
}
