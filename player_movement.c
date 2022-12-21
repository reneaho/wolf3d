/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 13:21:42 by raho              #+#    #+#             */
/*   Updated: 2022/12/21 15:05:11 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	update_movement(t_player *player, t_map *map)
{
	if (player->forward == 1)
	{
		if (map->matrix[player->collision.square_pos_y] \
						[player->collision.square_pos_x_plus_offset] == 0)
			player->pos_x += player->dir_x * player->move_speed;
		if (map->matrix[player->collision.square_pos_y_plus_offset] \
						[player->collision.square_pos_x] == 0)
			player->pos_y += player->dir_y * player->move_speed;
	}
	if (player->back == 1)
	{
		if (map->matrix[player->collision.square_pos_y] \
						[player->collision.square_pos_x_minus_offset] == 0)
			player->pos_x -= player->dir_x * player->move_speed;
		if (map->matrix[player->collision.square_pos_y_minus_offset] \
						[player->collision.square_pos_x] == 0)
			player->pos_y -= player->dir_y * player->move_speed;
	}
}

static void	limit_collision(t_player *player, t_map *map)
{
	int	x_offset;
	int	y_offset;

	x_offset = 0;
	y_offset = 0;
	if (player->dir_x < 0)
		x_offset = -15;
	else
		x_offset = 15;
	if (player->dir_y < 0)
		y_offset = -15;
	else
		y_offset = 15;
	player->collision.square_pos_x = player->pos_x / 64;
	player->collision.square_pos_x_plus_offset = \
										(player->pos_x + x_offset) / 64;
	player->collision.square_pos_x_minus_offset = \
										(player->pos_x - x_offset) / 64;
	player->collision.square_pos_y = player->pos_y / 64;
	player->collision.square_pos_y_plus_offset = \
										(player->pos_y + y_offset) / 64;
	player->collision.square_pos_y_minus_offset = \
										(player->pos_y - y_offset) / 64;
	update_movement(player, map);
}

void	add_movement(t_mlx *mlx)
{
	if (mlx->player.left == 1)
	{
		mlx->player.pos_angle += mlx->player.turn_speed;
		if (mlx->player.pos_angle >= 360)
			mlx->player.pos_angle -= 360;
		mlx->player.dir_x = cos(ft_deg_to_rad(mlx->player.pos_angle));
		mlx->player.dir_y = -sin(ft_deg_to_rad(mlx->player.pos_angle));
	}
	if (mlx->player.right == 1)
	{
		mlx->player.pos_angle -= mlx->player.turn_speed;
		if (mlx->player.pos_angle < 0)
			mlx->player.pos_angle += 360;
		mlx->player.dir_x = cos(ft_deg_to_rad(mlx->player.pos_angle));
		mlx->player.dir_y = -sin(ft_deg_to_rad(mlx->player.pos_angle));
	}
	if (mlx->player.forward == 1 || mlx->player.back == 1)
		limit_collision(&mlx->player, &mlx->map);
}
