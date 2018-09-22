/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptcalloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 16:09:20 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/22 13:07:59 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*ptcalloc(size_t nelem, size_t elsize)
{
	void	*ptr;
	size_t	size;

	size = nelem * elsize;
	//overflow
	if ((ptr = ptmalloc(size)))
		ft_memset(ptr, '\0', size);
	return (ptr);
}
