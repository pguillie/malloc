/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:09:41 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/14 17:56:33 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <stdlib.h>
//
# include <unistd.h>
# include <stdio.h>

# define MALLOC_ALIGN 15
//# define MALLOC_MIN_SIZE 16
//# define MALLOC_MAX_SIZE 4096
# define MALLOC_FREE_CHUNK 1

/*
********************************************************************************
**								   STRUCTURES
********************************************************************************
*/

/*
** S_MALLOC_CHUNK
**	- prev_size: size of the previous chunk
**	- size: size of the chunk (including overhead)
**	- prev: previous chunk in the free list
**	- next: next chunk in the free list
** The size is the total size of the chunk, including the overhead
** and the alignment.
** The memory asked by the user (and returned to them) begins at the `prev'
** address. This has 2 consequences :
**	* `prev' and `next' are only used for free chunks
**	* the minimal allocated size is 2 * sizeof(void *), and the minimal chunk
**	  size is 2 * sizeof(size_t) + 2 * sizeof(void *)
*/

typedef struct			s_malloc_chunk
{
	size_t					prev_size;
	size_t					size;
	struct s_malloc_chunk	*prev;
	struct s_malloc_chunk	*next;
}						t_malloc_chunk;

/*
** S_MALLOC_ARENA
**	- top: the top chunk of a mapped zone, always exist once a map is created
**	- next: the next mapped zone
*/

typedef struct			s_malloc_arena
{
	struct s_malloc_chunk	*top;
	struct s_malloc_arena	*next;
}						t_malloc_arena;

/*
** S_MALLOC_DATA
**	- arena: pointer to the first mapped zone
**	- large: linked list of `large' mallocs
**	- free:	array of pointers to the lists of `free' chunks
**		* the 7 first cells point to `free tiny' chunks, one for each size
**		  from 16 to 64 bytes, increasing by 8 bytes
**		* the last one is the list of `free small' chunks sorted by size
*/

typedef struct			s_malloc_data
{
	struct s_malloc_arena	*tiny;
	struct s_malloc_arena	*small;
	struct s_malloc_chunk	*large;
	struct s_malloc_chunk	*free[8];
}						t_malloc_data;

/*
********************************************************************************
**								   PROTOTYPES
********************************************************************************
*/

void					*malloc(size_t size);
void					*malloc_tiny(size_t size);
void					*malloc_small(size_t size);
void					*malloc_large(size_t size);
void					*malloc_top(t_malloc_arena **a, size_t s, size_t e);

void					free(void *ptr);
void					free_tiny(t_malloc_chunk *chunk);
void					free_small(t_malloc_chunk *chunk);
void					free_large(t_malloc_chunk *chunk);

void					*realloc(void *ptr, size_t size);

t_malloc_chunk			*get_tiny_chunk(void *ptr);
t_malloc_chunk			*get_small_chunk(void *ptr);
t_malloc_chunk			*get_large_chunk(void *ptr);

void					ft_show_alloc_mem();

//
void *ft_memcpy(void *src, void *dst, size_t n);

extern t_malloc_data	g_malloc_data;

#endif
