/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:09:41 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/25 18:57:50 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdarg.h>
# include <fcntl.h>

# include "malloc_struct.h"
# include "malloc_debug_var.h"
# include "../libft/includes/libft.h"

# define MALLOC_TINY_SIZE 128
# define MALLOC_SMALL_SIZE 4096
# define MALLOC_FREE_CHUNK 1

# define VERBOSE_SIZE 256

# define SHOW_FREE 1<<0

void			*malloc(size_t size);
void			*ptmalloc(size_t size);
void			*ptmalloc_tiny(size_t size);
void			*ptmalloc_small(size_t size);
void			*ptmalloc_large(size_t size);
void			*ptmalloc_top(t_malloc_arena **arena, size_t size, size_t elem);

void			free(void *ptr);
void			ptfree(void *ptr);
void			ptfree_tiny(t_malloc_chunk *chunk);
void			ptfree_small(t_malloc_chunk *chunk);
void			ptfree_small_insert(t_malloc_chunk *chunk);
void			ptfree_large(t_malloc_chunk *chunk);

void			*realloc(void *ptr, size_t size);
void			*reallocf(void *ptr, size_t size);
void			*ptrealloc(void *ptr, size_t size);
void			*ptrealloc_tiny(t_malloc_chunk *chunk, size_t size);
void			*ptrealloc_small(t_malloc_chunk *chunk, size_t size);
void			*ptrealloc_large(t_malloc_chunk *chunk, size_t size);
void			*ptrealloc_relocate(t_malloc_chunk *chunk,
		size_t size, void *data,
		void (*free_chunk)(t_malloc_chunk *));

void			*calloc(size_t nelem, size_t elsize);
void			*ptcalloc(size_t nelem, size_t elsize);

void			show_alloc_mem(void);
void			ptshow_alloc_mem(void);
void			show_alloc_mem_free(void);
void			ptshow_alloc_mem_free(void);
void			show_alloc_mem_total(size_t total);
size_t			show_alloc_tiny(t_malloc_arena *tiny, int mode);
size_t			show_alloc_small(t_malloc_arena *small, int mode);
size_t			show_alloc_large(t_malloc_chunk *large);

t_malloc_chunk	*get_tiny_chunk(void *ptr);
t_malloc_chunk	*get_small_chunk(void *ptr);
t_malloc_chunk	*get_large_chunk(void *ptr);

void			malloc_small_list_add(t_malloc_chunk *chunk);
void			malloc_small_list_remove(t_malloc_chunk *chunk);

void			malloc_init(void);
void			malloc_verbose(char *fmt, ...);
size_t			malloc_vrb_nbr(char *buff, size_t n);
size_t			malloc_vrb_ptr(char *buff, void *p);

void			abort_malloc(char *err, char mode);
void			abort_free(char *err, void *ptr, char mode);
void			abort_realloc(char *err, void *ptr, char mode);

extern t_malloc_data	g_malloc_data;
extern pthread_mutex_t	g_mutex;

#endif
