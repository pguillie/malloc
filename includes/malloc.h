/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:09:41 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/20 17:02:14 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <fcntl.h>

# include "malloc_struct.h"
# include "malloc_debug_var.h"
# include "../libft/includes/libft.h"

# define MALLOC_TINY_SIZE 128
# define MALLOC_SMALL_SIZE 4096
# define MALLOC_FREE_CHUNK 1

# define VERBOSE_SIZE 256

void			*malloc(size_t size);
void			*malloc_tiny(size_t size);
void			*malloc_small(size_t size);
void			*malloc_large(size_t size);
void			*malloc_top(t_malloc_arena **arena, size_t size, size_t elem);

void			free(void *ptr);
void			free_tiny(t_malloc_chunk *chunk);
void			free_small(t_malloc_chunk *chunk);
void			free_small_insert(t_malloc_chunk *chunk);
void			free_large(t_malloc_chunk *chunk);
t_malloc_chunk	*free_coalesce(t_malloc_chunk *chunk);

void			*realloc(void *ptr, size_t size);
void			*realloc_tiny(t_malloc_chunk *chunk, size_t size);
void			*realloc_small(t_malloc_chunk *chunk, size_t size);
void			*realloc_large(t_malloc_chunk *chunk, size_t size);
void			*realloc_relocate(t_malloc_chunk *chunk,
		size_t size, void *data,
		void (*free_chunk)(t_malloc_chunk *));

void			*calloc(size_t count, size_t size);

t_malloc_chunk	*get_tiny_chunk(void *ptr);
t_malloc_chunk	*get_small_chunk(void *ptr);
t_malloc_chunk	*get_large_chunk(void *ptr);

void			ft_show_alloc_mem();

void			malloc_init(void);
void			malloc_verbose(char *fmt, ...);

extern t_malloc_data	g_malloc_data;

#endif
