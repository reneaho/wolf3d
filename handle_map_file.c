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

int	count_squares(char *line)
{
	int	squares;
	int	i;

	squares = 0;
	i = 0;
	while (line[i + 1] != '\0')
	{
		if ((line[i] != ' ' && line[i] != '\t' && line[i] != '\n') && \
			(line[i + 1] == ' ' || line[i + 1] == '\t' || line[i + 1] == '\n'))
			squares++;
		i++;
	}
	if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
		squares++;
	return (squares);	
}

int	width_checks(int fd, int width, t_map *map)
{
	if (width == 0)
		errors_fd(EC_BADMAP, fd);
	if (map->width == 0)
		map->width = width;
	if (width != map->width)
		errors_fd(EC_BADMAP, fd);
}

int	get_map_dimensions(int fd, t_map *map)
{
	int		ret;
	int		width;
	char	*line;

	line = NULL;
	ret = get_next_line(fd, &line);
	while (ret > 0)
	{
		width = count_squares(line);
		width_checks(fd, width, map);
		map->height++;
		if (line)
		{
			free(line);
			line = NULL;
		}
		ret = get_next_line(fd, &line);
	}
	if (line)
		free(line);
	if (ret == -1)
		errors_fd(EC_GNL, fd);
	if (map->width < 3 || map->height < 3)
		errors_fd(EC_BADMAP, fd);
}

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
			while (line[index] != ' ' && line[index] != '\t' && line[index] != '\0')
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

void	save_map(char *filename, t_map *map)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		errors(EC_OPEN);
	get_map_dimensions(fd, map);
	if (close(fd) == -1)
		errors(EC_CLOSE);
	create_matrix_for_map(map);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		errors(EC_OPEN);
	copy_map_to_matrix(fd, map);
	if (close(fd) == -1)
		errors(EC_CLOSE);
	for (int y = 0; y < map->height; y++)
	{
		for (int x = 0; x < map->width; x++)
			printf("%d ", map->matrix[y][x]);
		printf("\n");
	}
}
