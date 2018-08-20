/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:31:49 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/20 16:16:15 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

void	malloc_init(void)
{
	char	*log_file;
	size_t	i;
	char	verbose;
	int		fd;

	verbose = 0;
	if (getenv("MALLOC_VERBOSE") || getenv("MallocVerbose"))
	{
		g_malloc_data.debug |= MALLOC_VERBOSE;
		verbose = 1;
		malloc_verbose("init", "verbose on", NULL, 0);
	}
	if (getenv("MALLOC_ERROR_ABORT") || getenv("MallocErrorAbort"))
	{
		g_malloc_data.debug |= MALLOC_ERROR_ABORT;
		if (verbose)
			malloc_verbose("init", "error abort on", NULL, 0);
	}
	if (getenv("MALLOC_CORRUPTION_ABORT") || getenv("MallocCorruptionAbort"))
	{
		g_malloc_data.debug |= MALLOC_CORRUPTION_ABORT;
		if (verbose)
			malloc_verbose("init", "corruption abort on", NULL, 0);
	}
	if ((log_file = getenv("MALLOC_LOG_FILE"))
		|| (log_file = getenv("MallocLogFile")))
	{
		i = 0;
		while (i < 126 && log_file[i])
		{
			g_malloc_data.log_file[i] = log_file[i];
			i++;
		}
		if (i && log_file[i] == '\0')
		{
			fd = open(log_file, O_CREAT | O_TRUNC, 0644);
			if (fd >= 0)
			{
				close(fd);
				g_malloc_data.debug |= MALLOC_LOG_FILE;
				if (verbose)
					malloc_verbose("init", "log file set", NULL, 0);
			}
		}
		malloc_verbose("init", "log file name too long", NULL, 0);
	}
	g_malloc_data.debug |= MALLOC_INIT;
}
