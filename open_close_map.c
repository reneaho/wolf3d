/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_close_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:23:25 by raho              #+#    #+#             */
/*   Updated: 2022/08/14 22:28:28 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	open_map(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Couldn't open: ", 2);
		ft_putendl_fd(filename, 2);
		exit (1);
	}
	return (fd);
}

void	close_map(int fd, t_map *map)
{
	if (close(fd) == -1)
	{
		ft_putstr_fd("Closing the file failed", 2);
		free_matrix(map->height, map);
		exit (1);
	}
}
