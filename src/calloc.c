/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 16:09:20 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/20 19:17:55 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*calloc(size_t count, size_t size)
{
	void			*ptr;
	unsigned char	*s;
	size_t			i;

	//overflow
	if (!(g_malloc_data.debug & MALLOC_INIT))
		malloc_init();
	if (g_malloc_data.debug & MALLOC_VERBOSE)
		malloc_verbose("CALLOC of %n objects of size %n\n", count, size);
	ptr = malloc(count * size);
	if (ptr)
	{
		s = (unsigned char *)ptr;
		i = count * size;
		while (i--)
			s[i] = '\0';
	}
	return (ptr);
}
