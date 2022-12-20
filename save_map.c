/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:42:51 by raho              #+#    #+#             */
/*   Updated: 2022/12/20 13:50:51 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	create_matrix_for_map(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	map->matrix = (int **)malloc(sizeof(int *) * map->height);
	if (map->matrix == NULL)
		errors(EC_MALLOC);
	while (y < map->height)
	{
		map->matrix[y] = (int *)malloc(sizeof(int) * map->width);
		if (map->matrix[y] == NULL)
			errors(EC_MALLOC);
		x = 0;
		while (x < map->width)
		{
			map->matrix[y][x] = 0;
			x++;
		}
		y++;
	}
}

static void	copy_map_to_matrix_helper(char *line, t_map *map)
{
	static int	y;
	int			x;
	int			index;

	x = 0;
	index = 0;
	while (line[index] != '\0')
	{
		if (line[index] != ' ' && line[index] != '\t')
		{
			map->matrix[y][x] = ft_atoi(&line[index]);
			x++;
			while (line[index] != ' ' && line[index] != '\t' && \
										line[index] != '\0')
				index++;
		}
		else
			index++;
	}
	y++;
}

static void	copy_map_to_matrix(int fd, t_map *map)
{
	int		ret;
	char	*line;

	line = NULL;
	ret = get_next_line(fd, &line);
	while (ret > 0)
	{
		copy_map_to_matrix_helper(line, map);
		if (line)
		{
			free(line);
			line = NULL;
		}
		ret = get_next_line(fd, &line);
	}
	if (line)
		free (line);
	if (ret == -1)
		errors_fd(EC_GNL, fd);
}

void	save_map(t_map *map, char *filename)
{
	int		fd;

	create_matrix_for_map(map);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		errors(EC_OPEN);
	copy_map_to_matrix(fd, map);
	if (close(fd) == -1)
		errors(EC_CLOSE);
}
