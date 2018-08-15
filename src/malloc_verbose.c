/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_verbose.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 14:35:43 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/15 16:39:11 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void malloc_verbose_function(char *fun)
{
	char	upper[16];
	size_t	i;
	size_t	j;

	upper[0] = '[';
	upper[1] = ' ';
	i = 0;
	j = 2;
	while (fun[i] && j < 14)
		upper[j++] = fun[i++] & ~32;
	upper[j++] = ' ';
	upper[j++] = ']';
	write(1, upper, j);
}

void malloc_verbose(char *fun, char *msg, void *ptr, size_t size)
{
	malloc_verbose_function(fun);
	if (msg)
	{
		write(1, " ", 1);
		write(1, msg, ft_strlen(msg));
	}
	if (ptr)
	{
		write(1, " ", 1);
		ft_putptr(ptr);
	}
	if (size)
	{
		write(1, " ", 1);
		ft_putnbr(size);
	}
	write(1, "\n", 1);
}
