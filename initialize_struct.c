/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:26:51 by raho              #+#    #+#             */
/*   Updated: 2022/08/21 16:59:16 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	initialize_struct(t_mlx *mlx)
{
	mlx->mlx_ptr = NULL;
	mlx->win_ptr = NULL;
	mlx->img.img_ptr = NULL;
	mlx->img.img_addr = NULL;
	mlx->img.bits_per_pixel = 0;
	mlx->img.size_line = 0;
	mlx->img.endian = 0;
	reinitialize_struct(mlx);
}

void	reinitialize_struct(t_mlx *mlx)
{
	mlx->draw.x = 0;
	mlx->draw.y = 0;
	mlx->draw.deltax = 0;
	mlx->draw.deltay = 0;
	mlx->draw.slope = 0;
	mlx->draw.parametric_value = 0;
	mlx->draw.temp = 0;
	mlx->draw.x1 = 0;
	mlx->draw.y1 = 0;
	mlx->draw.x2 = 0;
	mlx->draw.y2 = 0;
	/*mlx->iterations = 0;
	mlx->camera_x = 0;
	mlx->camera_y = 0;
	mlx->mouse_x = 0;
	mlx->mouse_y = 0;*/
}
