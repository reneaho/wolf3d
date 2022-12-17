/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 07:25:17 by raho              #+#    #+#             */
/*   Updated: 2022/12/17 07:45:45 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	draw_pixel(t_mlx *mlx)
{
	char	*pixel;
	
	if ((mlx->draw.x1 >= 0 && mlx->draw.x1 <= WINDOW_WIDTH) && \
		(mlx->draw.y1 >= 0 && mlx->draw.y1 <= WINDOW_HEIGHT))
	{
		pixel = mlx->img.img_addr + (((int)mlx->draw.y1 * mlx->img.size_line) + \
								((int)mlx->draw.x1 * (mlx->img.bits_per_pixel / 8)));
		*(int *)pixel = mlx->draw.color;
	}
}

static int	pick_pixel(t_mlx *mlx, int y)
{
	t_texture	*texture;
	char		*pixel;
	int			scaled_y;
	int			scaled_x;

	scaled_y = 256 * y / 64;
	scaled_x = 256 * mlx->raycast.wall_texture_offset / 64;

	if (mlx->player.compass == NORTH)
		texture = &mlx->texture[0];
	else if (mlx->player.compass == EAST)
		texture = &mlx->texture[1];
	else if (mlx->player.compass == SOUTH)
	{
		texture = &mlx->texture[2];
		scaled_x = 128 * mlx->raycast.wall_texture_offset / 64;
	}
	else if (mlx->player.compass == WEST)
		texture = &mlx->texture[3];
	pixel = texture->img_addr + ((scaled_y * texture->size_line) + \
			scaled_x * (texture->bits_per_pixel / 8));
	return (*(int *)pixel);
}

void	draw_column(int ray_nbr, t_mlx *mlx)
{
	int		projected_slice_height;
	int		y_starting_point;
	int		y_end_point;
	double	texture_y;
	double	texture_y_offset;
	double	texture_y_increment;

	mlx->draw.x1 = ray_nbr;
	mlx->draw.x2 = ray_nbr;
	mlx->draw.y1 = 0;
	mlx->draw.y2 = WINDOW_HEIGHT;

	projected_slice_height = (double)SQUARE_SIZE / mlx->raycast.closest_coll_dist * mlx->raycast.dist_to_proj_plane;
	
	texture_y_increment = (double)SQUARE_SIZE / (double)projected_slice_height;
	texture_y_offset = 0;

	if (projected_slice_height > WINDOW_HEIGHT)
	{
		texture_y_offset = (double)(projected_slice_height - WINDOW_HEIGHT) / 2.0;
		projected_slice_height = WINDOW_HEIGHT;
	}
	
	y_starting_point = (WINDOW_HEIGHT / 2) - (projected_slice_height / 2);
	y_end_point = y_starting_point + projected_slice_height;
	
	/* Draw the sky */

	if (projected_slice_height < WINDOW_HEIGHT)
	{
		
		mlx->draw.y2 = y_starting_point;
		mlx->draw.color = SOFT_SKY_BLUE;
		while (mlx->draw.y1 < mlx->draw.y2)
		{
			draw_pixel(mlx);
			mlx->draw.y1++;
		}
		mlx->draw.y2 = y_end_point;
	}

	texture_y = texture_y_offset * texture_y_increment;

	/* Draw the wall column */
	
	while (mlx->draw.y1 < mlx->draw.y2)
	{
		mlx->draw.color = pick_pixel(mlx, texture_y);
		draw_pixel(mlx);
		texture_y += texture_y_increment;
		mlx->draw.y1++;
	}

	/* Draw the floor */

	if (y_end_point < WINDOW_HEIGHT)
	{
		mlx->draw.y2 = WINDOW_HEIGHT;
		mlx->draw.color = MOSS_GREEN;
		while (mlx->draw.y1 < mlx->draw.y2)
		{
			draw_pixel(mlx);
			mlx->draw.y1++;
		}
	}
}
