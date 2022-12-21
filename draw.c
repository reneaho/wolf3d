/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 07:25:17 by raho              #+#    #+#             */
/*   Updated: 2022/12/21 15:08:56 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	draw_pixel(t_img *img, t_pointf point, int color)
{
	char	*pixel;

	if (((int)point.x >= 0 && (int)point.x <= WINDOW_WIDTH) && \
		((int)point.y >= 0 && (int)point.y <= WINDOW_HEIGHT))
	{
		pixel = img->img_addr + (((int)point.y * img->size_line) + \
								((int)point.x * (img->bits_per_pixel / 8)));
		*(int *)pixel = color;
	}
}

static int	pick_pixel(t_mlx *mlx, int y)
{
	t_texture	*texture;
	char		*pixel;
	int			scaled_y;
	int			scaled_x;

	texture = NULL;
	scaled_y = 256 * y / 64;
	scaled_x = 256 * mlx->raycast.wall_texture_xoffset / 64;
	if (mlx->player.compass == NORTH)
		texture = &mlx->texture[0];
	else if (mlx->player.compass == EAST)
		texture = &mlx->texture[1];
	else if (mlx->player.compass == SOUTH)
	{
		texture = &mlx->texture[2];
		scaled_x = 128 * mlx->raycast.wall_texture_xoffset / 64;
	}
	else if (mlx->player.compass == WEST)
		texture = &mlx->texture[3];
	pixel = texture->img_addr + ((scaled_y * texture->size_line) + \
			scaled_x * (texture->bits_per_pixel / 8));
	return (*(int *)pixel);
}

static void	draw_loops(t_mlx *mlx, t_pointf start, t_pointf end, float txtr_y)
{
	if (mlx->raycast.projected_slice_height < WINDOW_HEIGHT)
	{
		end.y = (WINDOW_HEIGHT / 2) - (mlx->raycast.projected_slice_height / 2);
		while (start.y < end.y)
		{
			draw_pixel(&mlx->img, start, SOFT_SKY_BLUE);
			start.y++;
		}
		end.y += mlx->raycast.projected_slice_height;
	}
	while (start.y < end.y)
	{
		draw_pixel(&mlx->img, start, pick_pixel(mlx, (int)txtr_y));
		txtr_y += mlx->raycast.wall_texture_yincrement;
		start.y++;
	}
	if (end.y < WINDOW_HEIGHT)
	{
		while (start.y < WINDOW_HEIGHT)
		{
			draw_pixel(&mlx->img, start, MOSS_GREEN);
			start.y++;
		}
	}
}

void	draw_column(t_mlx *mlx, int ray_nbr)
{
	t_raycast	*raycast;
	t_pointf	start;
	t_pointf	end;
	float		texture_y;

	raycast = &mlx->raycast;
	raycast->projected_slice_height = (float)SQUARE_SIZE / \
			raycast->closest_coll_dist * raycast->dist_to_proj_plane;
	raycast->wall_texture_yincrement = (float)SQUARE_SIZE / \
			(float)raycast->projected_slice_height;
	raycast->wall_texture_yoffset = 0;
	if (raycast->projected_slice_height > WINDOW_HEIGHT)
	{
		raycast->wall_texture_yoffset = \
			(raycast->projected_slice_height - WINDOW_HEIGHT) / 2;
		raycast->projected_slice_height = WINDOW_HEIGHT;
	}
	texture_y = raycast->wall_texture_yoffset * \
	raycast->wall_texture_yincrement;
	start.x = ray_nbr;
	start.y = 0;
	end.x = ray_nbr;
	end.y = WINDOW_HEIGHT;
	draw_loops(mlx, start, end, texture_y);
}
