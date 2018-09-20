/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:31:49 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/20 22:33:44 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_data	g_malloc_data;

static int	malloc_init_logfile(void)
{
	char	*log_file;
	size_t	i;
	int		fd;

	if ((log_file = getenv("MALLOC_LOG_FILE")))
	{
		i = 0;
		while (i < 126 && log_file[i])
		{
			g_malloc_data.log_file[i] = log_file[i];
			i++;
		}
		if (i && log_file[i] == '\0')
		{
			fd = open(log_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd >= 0)
			{
				close(fd);
				g_malloc_data.debug |= MALLOC_LOG_FILE;
				return (1);
			}
		}
		return (-1);
	}
	return (0);
}

void		malloc_init_abort(int verbose)
{
	if (getenv("MALLOC_ERROR_ABORT"))
	{
		g_malloc_data.debug |= MALLOC_ERROR_ABORT;
		if (verbose)
			malloc_verbose("set 'abort on error' on\n");
	}
	if (getenv("MALLOC_CORRUPTION_ABORT"))
	{
		g_malloc_data.debug |= MALLOC_CORRUPTION_ABORT;
		if (verbose)
			malloc_verbose("set 'abort on corruption' on\n");
	}
}

void		malloc_init(void)
{
	char	*value;
	int		verbose;

	verbose = malloc_init_logfile();
	if (verbose < 0)
		write(2, "malloc: unable to create or open logfile\n", 41);
	if ((value = getenv("MALLOC_VERBOSE")))
	{
		if (ft_strcmp(value, "42") == 0 || ft_strcmp(value, "full") == 0)
			g_malloc_data.debug |= MALLOC_FULL_VERBOSE;
		g_malloc_data.debug |= MALLOC_VERBOSE;
		verbose = 1;
		malloc_verbose("--- init ---\nset verbose on\n");
	}
	if (getenv("MALLOC_SCRIBLE"))
	{
		g_malloc_data.debug |= MALLOC_SCRIBLE;
		if (verbose)
			malloc_verbose("set scrible on\n");
	}
	malloc_init_abort(verbose);
	if (verbose)
		malloc_verbose("------------\n");
	g_malloc_data.debug |= MALLOC_INIT;
}
