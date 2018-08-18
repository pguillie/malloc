/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_verbose.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 14:35:43 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/18 14:13:37 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

void malloc_verbose_function(char *fun, int fd)
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
	write(fd, upper, j);
}

void malloc_verbose(char *fun, char *msg, void *ptr, size_t size)
{
	int fd;

	fd = 1;
	if (g_malloc_data.debug_var & MALLOC_LOG_FILE)
	{
		fd = open(g_malloc_data.log_file, O_WRONLY | O_APPEND);
		if (fd < 0)
			return ;
	}
	malloc_verbose_function(fun, fd);
	if (msg)
	{
		write(fd, " ", 1);
		write(fd, msg, ft_strlen(msg));
	}
	if (ptr)
	{
		write(fd, " ", 1);
		ft_putptr_fd(ptr, fd);
	}
	if (size)
	{
		write(fd, " ", 1);
		ft_putnbr_fd(size, fd);
	}
	write(fd, "\n", 1);
}
