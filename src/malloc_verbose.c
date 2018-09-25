/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_verbose.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 16:05:33 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/25 16:48:26 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

static size_t	malloc_putnbr_base(char *buff, size_t n, size_t base)
{
	size_t	i;

	i = 0;
	if (n >= base)
		i += malloc_putnbr_base(buff + i, n / base, base);
	buff[i++] = n % base > 9 ? n % base - 10 + 'A' : n % base + '0';
	return (i);
}

size_t			malloc_vrb_nbr(char *buff, size_t n)
{
	return (malloc_putnbr_base(buff, n, 10));
}

size_t			malloc_vrb_ptr(char *buff, void *p)
{
	if (p == NULL)
	{
		ft_memcpy(buff, "(null)", 6);
		return (6);
	}
	ft_memcpy(buff, "0x", 2);
	return (2 + malloc_putnbr_base(buff + 2, (size_t)p, 16));
}

static void		malloc_verbose_write(char *buff, size_t len)
{
	int	fd;

	if (g_malloc_data.debug & MALLOC_LOG_FILE)
	{
		fd = open(g_malloc_data.log_file, O_WRONLY | O_APPEND);
		if (fd >= 0)
			write(fd, buff, len);
	}
	else
		write(1, buff, len);
}

void			malloc_verbose(char *fmt, ...)
{
	char	buff[VERBOSE_SIZE];
	va_list	ap;
	size_t	i;

	va_start(ap, fmt);
	ft_memset(buff, 0, VERBOSE_SIZE);
	i = 0;
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			if (*fmt == 'n')
				i += malloc_vrb_nbr(buff + i, va_arg(ap, size_t));
			else if (*fmt == 'p')
				i += malloc_vrb_ptr(buff + i, va_arg(ap, void *));
		}
		else
			buff[i++] = *fmt;
		fmt++;
	}
	va_end(ap);
	malloc_verbose_write(buff, i);
}
