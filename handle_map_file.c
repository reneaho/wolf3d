/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 02:43:56 by raho              #+#    #+#             */
/*   Updated: 2022/12/17 08:50:12 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	create_matrix_for_map(t_map *map)
{
	int	index;

	index = 0;
	map->matrix = (int **)malloc(sizeof(int *) * map->height);
	if (map->matrix == NULL)
		exit(1);
	while (index < map->height)
	{
		map->matrix[index] = (int *)malloc(sizeof(int) * map->width);
		if (map->matrix[index] == NULL)
			exit (1);
		ft_bzero((int *)map->matrix[index], map->width);
		index++;
	}
}

void	get_map_dimensions(int fd, t_map *map)
{
	int		ret;
	int		index;
	char	buff[READ_BUFF + 1];

	map->width_counter = 0;
	map->height = 1;
	ret = read(fd, buff, READ_BUFF);
	index = 0;
	while (ret > 0)
	{
		buff[ret] = '\0';
		while (index < ret && buff[index] != '\0')
		{
			if (buff[index] != ' ' && (buff[index + 1] == ' ' || buff[index + 1] == '\n'))
				map->width_counter++;
			if (buff[index] == '\n')
			{
				if (map->width == 0)
					map->width = map->width_counter;
				else
				{
					if (map->width != map->width_counter)
					{
						ft_putendl_fd("bad map", 2);
						exit (1);
					}
				}
				map->width_counter = 0;
				map->height++;
			}
			index++;
		}
		ret = read(fd, buff, READ_BUFF);
	}
}

static void	copy_map_to_matrix_helper(char *buff, t_map *map)
{
	static int	x = 0;
	static int	y = 0;

	map->matrix[y][x] = ft_atoi(buff);
	x++;
	if (x == map->width)
	{
		y++;
		x = 0;
	}
}

static void	copy_map_to_matrix(int fd, t_map *map)
{
	int		ret;
	int		index;
	char	buff[READ_BUFF + 1];

	ret = read(fd, buff, READ_BUFF);
	index = 0;
	while (ret > 0)
	{
		buff[ret] = '\0';
		while (index != ret)
		{
			if (buff[index] != '\n' && buff[index] != ' ')
				copy_map_to_matrix_helper(&buff[index], map);
			index++;
		}
		ret = read(fd, buff, READ_BUFF);
	}
}

void	save_map(char *filename, t_map *map)
{
	int		fd;

	fd = open_map(filename);
	get_map_dimensions(fd, map);
	close_map(fd, map);
	create_matrix_for_map(map);
	fd = open_map(filename);
	copy_map_to_matrix(fd, map);
	close_map(fd, map);
}
