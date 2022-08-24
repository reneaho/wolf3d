/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:25:14 by raho              #+#    #+#             */
/*   Updated: 2022/08/21 16:53:55 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	image_pixel_put(int color, int x, int y, t_mlx *mlx)
{
	char	*pixel;

	pixel = mlx->img.img_addr + ((y * mlx->img.size_line) + (x * \
								(mlx->img.bits_per_pixel / 8)));
	*(int *)pixel = color;
}

int	check_if_inside(int x, int y)
{
	if ((x >= 0 && x < WINDOW_SIZE_WIDTH) && (y >= 0 && y < WINDOW_SIZE_HEIGHT))
		return (1);
	else
		return (0);
}

void	erase_map(t_mlx *mlx)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_SIZE_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_SIZE_WIDTH)
		{
			image_pixel_put(0, x, y, mlx);
			x++;
		}
		y++;
	}
}
