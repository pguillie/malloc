/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_verbose.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 16:05:33 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/20 21:46:07 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

static size_t	malloc_putnbr_base(size_t n, char *buff, size_t i, size_t base)
{
	if (n >= base)
		i = malloc_putnbr_base(n / base, buff, i, base);
	buff[i++] = n % base > 9 ? n % base - 10 + 'A' : n % base + '0';
	return (i);
}

static size_t	malloc_vrb_nbr(size_t n, char *buff, size_t i)
{
	return (malloc_putnbr_base(n, buff, i, 10));
}

static size_t	malloc_vrb_ptr(void *p, char *buff, size_t i)
{
	if (p == NULL)
	{
		ft_memcpy(buff + i, "(null)", 6);
		return (i + 6);
	}
	buff[i++] = '0';
	buff[i++] = 'x';
	return (malloc_putnbr_base((size_t)p, buff, i, 16));
}

static void		malloc_verbose_write(char *buff, size_t i)
{
	int	fd;

	if (g_malloc_data.debug & MALLOC_LOG_FILE)
	{
		fd = open(g_malloc_data.log_file, O_WRONLY | O_APPEND);
		if (fd >= 0)
			write(fd, buff, i);
	}
	else
		write(1, buff, i);
}

void			malloc_verbose(char *fmt, ...)
{
	char	buff[VERBOSE_SIZE];
	va_list	ap;
	size_t	i;

	va_start(ap, fmt);
	ft_bzero(buff, VERBOSE_SIZE);
	i = 0;
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			if (*fmt == 'n')
				i = malloc_vrb_nbr(va_arg(ap, size_t), buff, i);
			else if (*fmt == 'p')
				i = malloc_vrb_ptr(va_arg(ap, void *), buff, i);
		}
		else
			buff[i++] = *fmt;
		fmt++;
	}
	va_end(ap);
	malloc_verbose_write(buff, i);
}
