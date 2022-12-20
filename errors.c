/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 02:43:56 by raho              #+#    #+#             */
/*   Updated: 2022/12/20 12:54:34 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	errors(int error_code)
{
	if (error_code == EC_OPEN)
		ft_putendl_fd("error: opening the map failed", 2);
	if (error_code == EC_CLOSE)
		ft_putendl_fd("error: closing the map failed", 2);
	if (error_code == EC_MALLOC)
		ft_putendl_fd("error: malloc failed", 2);
	exit (-1);
}

void	errors_fd(int error_code, int fd)
{
	if (error_code == EC_GNL)
		ft_putendl_fd("error: reading the map with get_next_line failed", 2);
	if (error_code == EC_BADMAP)
		ft_putendl_fd("error: bad map", 2);
	if (close(fd) == -1)
		errors(EC_CLOSE);
	exit (-1);
}
