/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 16:05:33 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/19 18:04:52 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static size_t	malloc_print_fct(va_list ap, char *buff, size_t i)
{
	char	*f;

	f = va_arg(ap, char *);
	buff[i++] = '[';
	while (*f)
		buff[i++] = *f++;
	buff[i++] = ']';
	return (i);
}

static size_t	malloc_print_nbr(va_list ap, char *buff, size_t i)
{
	size_t	n;

	n = va_arg(ap, size_t);
	(void)buff; (void)i;
	return (0);
}

static size_t	malloc_print_ptr(va_list ap, char *buff, size_t i)
{
	void	*p;

	p = va_arg(ap, void *);
	(void)buff; (void)i;
	return (0);
}

static size_t	malloc_print_str(va_list ap, char *buff, size_t i)
{
	char	*s;

	s = va_arg(ap, char *);
	while (*s)
		buff[i++] = *s++;
	return (i);
}

void			malloc_print(char *fmt, ...)
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
			if (*fmt == 'f')
				i = malloc_print_fct(ap, buff, i);
			else if (*fmt == 'n')
				i = malloc_print_nbr(ap, buff, i);
			else if (*fmt == 'p')
				i = malloc_print_ptr(ap, buff, i);
			else if (*fmt == 's')
				i = malloc_print_str(ap, buff, i);
		}
		else
			buff[i++] = *fmt;
		fmt++;
	}
	write(1, buff, i);
	va_end(ap);
}
