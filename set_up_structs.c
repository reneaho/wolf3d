/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_structs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 02:45:37 by raho              #+#    #+#             */
/*   Updated: 2022/09/02 03:33:15 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	set_up_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, \
					WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT, "wolf3d");
	mlx->mouse = 1;
	mlx->img.bits_per_pixel = 0;
	mlx->img.size_line = 0;
	mlx->img.endian = 0;
}

static void	set_up_draw(t_draw *draw)
{
	draw->x = 0;
	draw->y = 0;
	draw->deltax = 0;
	draw->deltay = 0;
	draw->slope = 0;
	draw->parametric_value = 0;
	draw->temp = 0;
	draw->x1 = 0;
	draw->y1 = 0;
	draw->x2 = 0;
	draw->y2 = 0;
}

static void	set_up_player(t_player *player)
{
	player->pos_angle = 0;
	player->pos_x = 200;
	player->pos_y = 350;
	player->pos_dx = cos(player->pos_angle);
	player->pos_dy = sin(player->pos_angle);
	player->ray_cpoint_x = 0;
	player->ray_cpoint_y = 0;
	player->color = 0xFF0000;
}

void	set_up_map(t_map *map)
{
	map->width = 0;
	map->width_counter = 1;
	map->height = 1;
	map->wall_w = 0;
	map->wall_h = 0;
}

void	set_up_structs(t_mlx *mlx)
{
	set_up_mlx(mlx);
	set_up_player(&mlx->player);
	set_up_map(&mlx->map);
	set_up_draw(&mlx->draw);
}
