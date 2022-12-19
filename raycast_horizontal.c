/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_horizontal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 07:17:22 by raho              #+#    #+#             */
/*   Updated: 2022/12/17 07:46:42 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

// First check is for when the player is facing north, second one is for south
int	find_hor_coll_point(t_mlx *mlx)
{
	if (mlx->raycast.ray_angle > 0.0 && mlx->raycast.ray_angle < 180.0)
	{
		mlx->raycast.ray_y = (((int)mlx->player.pos_y >> 6) << 6) - 0.0001;
		mlx->raycast.ray_x = mlx->player.pos_x + \
			(mlx->player.pos_y - mlx->raycast.ray_y) / \
			tan(ft_deg_to_rad(mlx->raycast.ray_angle));
		mlx->raycast.offset_y = -SQUARE_SIZE;
		mlx->raycast.offset_x = -mlx->raycast.offset_y / \
			tan(ft_deg_to_rad(mlx->raycast.ray_angle));
	}
	else  if (mlx->raycast.ray_angle > 180.0 && mlx->raycast.ray_angle < 360.0)
	{
		mlx->raycast.ray_y = (((int)mlx->player.pos_y >> 6) << 6) + SQUARE_SIZE;
		mlx->raycast.ray_x = mlx->player.pos_x + \
			(mlx->player.pos_y - mlx->raycast.ray_y) / \
			tan(ft_deg_to_rad(mlx->raycast.ray_angle));
		mlx->raycast.offset_y = SQUARE_SIZE;
		mlx->raycast.offset_x = -mlx->raycast.offset_y / \
			tan(ft_deg_to_rad(mlx->raycast.ray_angle));
	}
	else
		return (0);
	return (1);
}

double	calc_hor_coll_dist(t_mlx *mlx)
{
	int	index;

	index = 0;
	while (index < mlx->map.height)
	{
		mlx->raycast.map_x = ((int)mlx->raycast.ray_x) >> 6;
		mlx->raycast.map_y = ((int)mlx->raycast.ray_y) >> 6;
		if (mlx->raycast.map_x >= 0 && mlx->raycast.map_x < mlx->map.width && \
			mlx->raycast.map_y >= 0 && mlx->raycast.map_y < mlx->map.height && \
			mlx->map.matrix[mlx->raycast.map_y][mlx->raycast.map_x] != 0)
		{
			mlx->raycast.hor_coll_point_x = mlx->raycast.ray_x;
			return (ray_collision_distance(&mlx->player, \
				mlx->raycast.ray_x, mlx->raycast.ray_y));
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

void	save_horizontal(t_mlx *mlx, double hor_coll_dist)
{
	mlx->raycast.closest_coll_dist = hor_coll_dist;
	mlx->raycast.wall_texture_xoffset = (int)mlx->raycast.hor_coll_point_x % SQUARE_SIZE;
	if (mlx->raycast.ray_angle > 0.0 && mlx->raycast.ray_angle < 180.0)
		mlx->player.compass = NORTH;
	else
		mlx->player.compass = SOUTH;
}
