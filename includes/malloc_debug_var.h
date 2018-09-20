/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_debug_var.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 11:50:30 by pguillie          #+#    #+#             */
/*   Updated: 2018/09/20 22:32:46 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_DEBUG_VAR_H
# define MALLOC_DEBUG_VAR_H

# define MALLOC_INIT 1<<0
# define MALLOC_LOG_FILE 1<<1
# define MALLOC_VERBOSE 1<<2
# define MALLOC_FULL_VERBOSE 1<<3
# define MALLOC_CORRUPTION_ABORT 1<<4
# define MALLOC_ERROR_ABORT 3<<4
# define MALLOC_SCRIBLE 1<<6

#endif
