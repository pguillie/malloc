#include "malloc.h"

t_malloc_data	g_malloc_data;

static t_malloc_arena	*ft_malloc_arena()
{
	t_malloc_arena	*arena;
	size_t			align;
	size_t			length;

	align = getpagesize() - 1;
	length = 100 * (4 * sizeof(size_t) + 64 + 4096) + align & ~align;
	arena = (t_malloc_arena *)mmap(NULL, length, PROT_READ | PROT_WRITE,
								   MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (arena == MAP_FAILED)
		return (NULL);
	arena->top = (t_malloc_chunk *)arena + sizeof(t_malloc_arena);
	arena->top->prev_size = 0;
	arena->top->size = length - sizeof(t_malloc_arena);
	arena->next = NULL;
	return (arena);
}

static t_malloc_arena	*ft_malloc_get_arena(size_t size)
{
	t_malloc_arena	*arena;
	
	if (g_malloc_data.arena)
	{
		arena = g_malloc_data.arena;
		while (arena->top->size < size + sizeof(t_malloc_chunk))
		{
			if (arena->next == NULL)
			{
				arena->next = ft_malloc_arena();
				if (arena->next = NULL)
					return (NULL);
			}
			arena = arena->next;
		}
	}
	else
	{
		g_malloc_data.arena = ft_malloc_arena()
		arena = g_malloc_data.arena;
	}
	return (arena);
}

void					*ft_malloc_top(size_t size)
{
	t_malloc_arena	*arena;
	t_malloc_chunk	*chunk;
	size_t			align;

	size = size + 2 * sizeof(t_size) + 7 & ~7;
	arena = ft_malloc_get_arena(size);
	if (arena == NULL)
		return (NULL);
	chunk = arena->top;
	arena->top += size;											/* cast ? */
	arena->top->prev_size = size;
	arena->top->size = chunk->size - size;
	chunk->size = size;
	return ((void *)chunk + 2 * sizeof(size_t));
}
