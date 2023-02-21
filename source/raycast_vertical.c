/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_vertical.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 07:19:42 by raho              #+#    #+#             */
/*   Updated: 2022/12/21 15:10:33 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

// First check is for when the player is facing west, second one is for east
int	find_ver_coll_point(t_mlx *mlx)
{
	if (mlx->raycast.ray_angle > 90 && mlx->raycast.ray_angle < 270)
	{
		mlx->raycast.ray_x = (((int)mlx->player.pos_x >> 6) << 6) - 0.001f;
		mlx->raycast.ray_y = mlx->player.pos_y + \
			(mlx->player.pos_x - mlx->raycast.ray_x) * \
			tan(ft_deg_to_rad(mlx->raycast.ray_angle));
		mlx->raycast.offset_x = -SQUARE_SIZE;
		mlx->raycast.offset_y = -mlx->raycast.offset_x * \
			tan(ft_deg_to_rad(mlx->raycast.ray_angle));
	}
	else if ((mlx->raycast.ray_angle > 270 && \
			mlx->raycast.ray_angle <= 360) || \
			(mlx->raycast.ray_angle >= 0 && mlx->raycast.ray_angle < 90))
	{
		mlx->raycast.ray_x = (((int)mlx->player.pos_x >> 6) << 6) + SQUARE_SIZE;
		mlx->raycast.ray_y = mlx->player.pos_y + \
			(mlx->player.pos_x - mlx->raycast.ray_x) * \
			tan(ft_deg_to_rad(mlx->raycast.ray_angle));
		mlx->raycast.offset_x = SQUARE_SIZE;
		mlx->raycast.offset_y = -mlx->raycast.offset_x * \
			tan(ft_deg_to_rad(mlx->raycast.ray_angle));
	}
	else
		return (0);
	return (1);
}

float	calc_ver_coll_dist(t_mlx *mlx)
{
	int	index;

	index = 0;
	while (index < mlx->map.width)
	{
		mlx->raycast.map_x = ((int)mlx->raycast.ray_x) >> 6;
		mlx->raycast.map_y = ((int)mlx->raycast.ray_y) >> 6;
		if (mlx->raycast.map_x >= 0 && mlx->raycast.map_x < mlx->map.width && \
			mlx->raycast.map_y >= 0 && mlx->raycast.map_y < mlx->map.height && \
			mlx->map.matrix[mlx->raycast.map_y][mlx->raycast.map_x] != 0)
		{
			mlx->raycast.ver_coll_point_y = mlx->raycast.ray_y;
			return (ray_collision_distance(&mlx->player, \
				(t_pointf){mlx->raycast.ray_x, mlx->raycast.ray_y}));
		}
		else
		{
			mlx->raycast.ray_x += mlx->raycast.offset_x;
			mlx->raycast.ray_y += mlx->raycast.offset_y;
			index++;
		}
	}
	return (100000);
}

void	save_vertical(t_mlx *mlx, float ver_coll_dist)
{
	mlx->raycast.closest_coll_dist = ver_coll_dist;
	mlx->raycast.wall_texture_xoffset = (int)mlx->raycast.ver_coll_point_y % \
		SQUARE_SIZE;
	if (mlx->raycast.ray_angle > 90 && mlx->raycast.ray_angle < 270)
		mlx->player.compass = WEST;
	else
		mlx->player.compass = EAST;
}
