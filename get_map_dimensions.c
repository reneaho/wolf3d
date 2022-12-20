/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_dimensions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 02:43:56 by raho              #+#    #+#             */
/*   Updated: 2022/12/20 13:50:21 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	count_squares(char *line)
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

static void	width_checks(t_map *map, int fd, int width)
{
	if (width == 0)
		errors_fd(EC_BADMAP, fd);
	if (map->width == 0)
		map->width = width;
	if (width != map->width)
		errors_fd(EC_BADMAP, fd);
}

static void	get_map_dimensions(t_map *map, int fd)
{
	int		ret;
	int		width;
	char	*line;

	line = NULL;
	ret = get_next_line(fd, &line);
	while (ret > 0)
	{
		width = count_squares(line);
		width_checks(map, fd, width);
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

void	read_map(t_map *map, char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		errors(EC_OPEN);
	get_map_dimensions(map, fd);
	if (close(fd) == -1)
		errors(EC_CLOSE);
}
