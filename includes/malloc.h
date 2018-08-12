/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:09:41 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/12 17:11:14 by pguillie         ###   ########.fr       */
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

void					*ft_malloc(size_t size);
void					ft_free(void *ptr);
void					*ft_realloc(void *ptr, size_t size);

void					ft_show_alloc_mem();

extern t_malloc_data	g_malloc_data;

#endif
