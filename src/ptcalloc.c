/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptcalloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 16:09:20 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/25 18:41:14 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*ptcalloc(size_t nelem, size_t elsize)
{
	void	*ptr;
	size_t	size;

	size = nelem * elsize;
	if (nelem > (size_t)(0 - 1) / elsize)
		return (NULL);
	if ((ptr = ptmalloc(size)))
		ft_memset(ptr, '\0', size);
	return (ptr);
}
