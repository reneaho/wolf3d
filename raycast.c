/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:35:05 by raho              #+#    #+#             */
/*   Updated: 2022/12/17 07:40:45 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double	ray_collision_distance(t_player *player, double coll_x, double coll_y)
{
	double	distance;
	double	temp;

	temp = ((player->pos_x * player->pos_x) - \
			(2.0 * player->pos_x * coll_x) + \
			(coll_x * coll_x)) + \
			((player->pos_y * player->pos_y) - \
			(2.0 * player->pos_y * coll_y) + \
			(coll_y * coll_y));
	distance = ft_sqrtd(temp);
	return (distance);
}

void	raycast(t_mlx *mlx)
{
	double	hor_coll_dist;
	double	ver_coll_dist;
	double	fish_eye_fix_beta;

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
	mlx->raycast.closest_coll_dist = mlx->raycast.closest_coll_dist * cos(ft_deg_to_rad(fish_eye_fix_beta));
}
