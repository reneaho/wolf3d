/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 02:45:37 by raho              #+#    #+#             */
/*   Updated: 2022/12/17 07:51:00 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	init_more_textures(t_mlx *mlx)
{
	t_texture	*texture;
	
	texture = &mlx->texture[3];
	texture->img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "wall_textures/rock4.xpm", &texture->img_width, &texture->img_height);
	if (texture->img_ptr == NULL)
		exit (1);
	texture->img_addr = mlx_get_data_addr(texture->img_ptr, &texture->bits_per_pixel, &texture->size_line, &texture->endian);
	if (texture->img_addr == NULL)
		exit (1);
}

void	init_textures(t_mlx *mlx)
{
	t_texture	*texture;

	texture = &mlx->texture[0];
	texture->img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "wall_textures/rock1.xpm", &texture->img_width, &texture->img_height);
	if (texture->img_ptr == NULL)
		exit (1);
	texture->img_addr = mlx_get_data_addr(texture->img_ptr, &texture->bits_per_pixel, &texture->size_line, &texture->endian);
	if (texture->img_addr == NULL)
		exit (1);
	texture = &mlx->texture[1];
	texture->img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "wall_textures/rock2.xpm", &texture->img_width, &texture->img_height);
	if (texture->img_ptr == NULL)
		exit (1);
	texture->img_addr = mlx_get_data_addr(texture->img_ptr, &texture->bits_per_pixel, &texture->size_line, &texture->endian);
	if (texture->img_addr == NULL)
		exit (1);
	texture = &mlx->texture[2];
	texture->img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "wall_textures/rock3.xpm", &texture->img_width, &texture->img_height);
	if (texture->img_ptr == NULL)
		exit (1);
	texture->img_addr = mlx_get_data_addr(texture->img_ptr, &texture->bits_per_pixel, &texture->size_line, &texture->endian);
	if (texture->img_addr == NULL)
		exit (1);
	init_more_textures(mlx);
}
