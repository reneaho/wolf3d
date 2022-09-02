/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 07:26:13 by raho              #+#    #+#             */
/*   Updated: 2022/09/02 08:44:54 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

void	cast_rays(t_player *player, t_map *map)
{
	int	index;
	int	map_x;
	int	map_y;
	double	a_tan;

	(void)map;
	(void)map_x;
	(void)map_y;
	player->ray_angle = player->pos_angle;
	index = 0;
	while (index < 1)
	{
		// horizontal grid lines
		player->depth_of_field = 0;
		a_tan = -1 / tan(player->ray_angle);
		if (player->ray_angle > M_PI) // looking down
		{
			player->ray_y = (((int)player->pos_y >> 6) << 6) - 0.0001;
			player->ray_x = (player->pos_y - player->ray_y) * a_tan + player->pos_x;
			player->offset_y = -64;
			player->offset_x = -player->offset_y * a_tan;
		}
		if (player->ray_angle < M_PI) // looking up
		{
			player->ray_y = (((int)player->pos_y >> 6) << 6) + 64;
			player->ray_x = (player->pos_y - player->ray_y) * a_tan + player->pos_x;
			player->offset_y = 64;
			player->offset_x = -player->offset_y * a_tan;
		}
		if (player->ray_angle == 0 || player->ray_angle == M_PI) // looking left or right
		{
			player->ray_x = player->pos_x;
			player->ray_y = player->pos_y;
			player->depth_of_field = 8;
		}
		printf("player->ray_x: %f\n", player->ray_x);
		printf("player->ray_y: %f\n", player->ray_y);
		printf("player->offset_x: %f\n", player->offset_x);
		printf("player->offset_y: %f\n", player->offset_y);
		printf("player->ray_angle: %f\n", player->ray_angle);
		printf("player->depth_of_field: %f\n", player->depth_of_field);
		printf("player->pos_angle: %f\n", player->pos_angle);
		index++;
	}
}
/*
void	ray_casting(t_mlx *mlx)
{
	int	x;

	x = 0;
	while (x < WINDOW_SIZE_WIDTH)
	{
		player->camera_x = 2 * x / (double)WINDOW_SIZE_WIDTH - 1;
		player->offset_x = player->dir_x + player->plane_x * player->camera_x;
		player->offset_y = player->dir_y + player->plane_y * player->camera_x;
		x++;
	}
}
*/