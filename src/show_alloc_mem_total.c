/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_total.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 17:33:43 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/25 17:34:30 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	show_alloc_mem_total(size_t total)
{
	char	buff[64];
	size_t	i;

	ft_memcpy(buff, "Total : ", 8);
	i = 8;
	i += malloc_vrb_nbr(buff + i, total);
	ft_memcpy(buff + i, " octets\n", 8);
	i += 8;
	write(1, buff, i);
}
