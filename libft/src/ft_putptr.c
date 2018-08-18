/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 15:44:11 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/18 14:43:32 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_putptr_fd(void *ptr, int fd)
{
	size_t	n;
	size_t	i;
	char	c;

	n = (size_t)ptr;
	write(fd, "0x", 2);
	i = 1L << 60;
	while (i)
	{
		c = n / i > 9 ? n / i + 'A' - 10 : n / i + '0';
		n = n - n / i * i;
		write(fd, &c, 1);
		i /= 16;
	}
}

void ft_putptr(void *ptr)
{
	size_t	n;
	size_t	i;
	char	c;

	n = (size_t)ptr;
	write(1, "0x", 2);
	i = 1L << 60;
	while (i)
	{
		c = n / i > 9 ? n / i + 'A' - 10 : n / i + '0';
		n = n - n / i * i;
		write(1, &c, 1);
		i /= 16;
	}
}
