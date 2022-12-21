/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:35:05 by raho              #+#    #+#             */
/*   Updated: 2022/12/21 15:12:47 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

float	ray_collision_distance(t_player *player, t_pointf collision)
{
	float	distance;
	float	temp;

	temp = ((player->pos_x * player->pos_x) - \
			(2.0f * player->pos_x * collision.x) + \
			(collision.x * collision.x)) + \
			((player->pos_y * player->pos_y) - \
			(2.0f * player->pos_y * collision.y) + \
			(collision.y * collision.y));
	distance = ft_sqrtf(temp);
	return (distance);
}

void	raycast(t_mlx *mlx)
{
	float	hor_coll_dist;
	float	ver_coll_dist;
	float	fish_eye_fix_beta;

	hor_coll_dist = 100000;
	ver_coll_dist = 100000;
	if (find_hor_coll_point(mlx))
		hor_coll_dist = calc_hor_coll_dist(mlx);
	if (find_ver_coll_point(mlx))
		ver_coll_dist = calc_ver_coll_dist(mlx);
	if (ver_coll_dist < hor_coll_dist)
		save_vertical(mlx, ver_coll_dist);
	else
		save_horizontal(mlx, hor_coll_dist);
	fish_eye_fix_beta = mlx->player.pos_angle - mlx->raycast.ray_angle;
	mlx->raycast.closest_coll_dist = mlx->raycast.closest_coll_dist * \
									cos(ft_deg_to_rad(fish_eye_fix_beta));
}
