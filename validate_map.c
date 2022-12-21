/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 13:40:11 by raho              #+#    #+#             */
/*   Updated: 2022/12/20 13:59:40 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	check_horizontal_borders(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < map->width)
	{
		if (map->matrix[y][x] == 0)
			errors(EC_BADMAP);
		x++;
	}
	x = 0;
	y = map->height - 1;
	while (x < map->width)
	{
		if (map->matrix[y][x] == 0)
			errors(EC_BADMAP);
		x++;
	}
}

static void	check_vertical_borders(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < map->height)
	{
		if (map->matrix[y][x] == 0)
			errors(EC_BADMAP);
		y++;
	}
	x = map->width - 1;
	y = 0;
	while (y < map->height)
	{
		if (map->matrix[y][x] == 0)
			errors(EC_BADMAP);
		y++;
	}
}

void	validate_map(t_map *map)
{
	check_horizontal_borders(map);
	check_vertical_borders(map);
}
