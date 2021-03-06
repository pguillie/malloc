/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 10:57:47 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/22 15:23:41 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	ft_error_ptr(void *ptr)
{
	size_t	n;
	size_t	i;
	char	c;

	write(2, "0x", 2);
	n = (size_t)ptr;
	i = 1L << 60;
	while (i)
	{
		c = n / i;
		c = (c > 9 ? c - 10 + 'a' : c + '0');
		write(2, &c, 1);
		n = n - n / i * i;
		i /= 16;
	}
}

void		abort_malloc(char *err, char mode)
{
	if (g_malloc_data.debug & mode)
	{
		write(2, "Error: malloc(): ", 17);
		write(2, err, ft_strlen(err));
		write(2, "\n", 1);
		abort();
	}
}

void		abort_free(char *err, void *ptr, char mode)
{
	if (g_malloc_data.debug & mode)
	{
		write(2, "Error: free(): ", 15);
		write(2, err, ft_strlen(err));
		write(2, ": ", 2);
		ft_error_ptr(ptr);
		write(2, "\n", 1);
		abort();
	}
}

void		abort_realloc(char *err, void *ptr, char mode)
{
	if (g_malloc_data.debug & mode)
	{
		write(2, "Error: realloc(): ", 18);
		write(2, err, ft_strlen(err));
		write(2, ": ", 2);
		ft_error_ptr(ptr);
		write(2, "\n", 1);
		abort();
	}
}
