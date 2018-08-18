/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 11:22:46 by pguillie          #+#    #+#             */
/*   Updated: 2018/08/18 14:12:02 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>

void	*ft_memcpy(void *src, void *dst, size_t n);
void	ft_putnbr(size_t n);
void	ft_putnbr_fd(size_t n, int fd);
void	ft_putptr(void *ptr);
void	ft_putptr_fd(void *ptr, int fd);
void	ft_putstr(char *str);
void	ft_putstr_fd(char *str, int fd);
size_t	ft_strlen(char *str);

#endif
