/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:05:05 by raho              #+#    #+#             */
/*   Updated: 2022/08/21 16:38:10 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	positive_negative_undefined_slope_2(t_mlx *mlx)
{
	if (mlx->draw.slope < 1 && mlx->draw.y1 < mlx->draw.y2)
		mlx->draw.y = mlx->draw.y + 1;
	else
		mlx->draw.y = mlx->draw.y - 1;
	mlx->draw.parametric_value = mlx->draw.parametric_value + 2 * \
							mlx->draw.deltay - 2 * mlx->draw.deltax;
}

static void	positive_negative_undefined_slope_1(t_mlx *mlx)
{
	if (mlx->draw.x1 > mlx->draw.x2)
	{
		mlx->draw.temp = mlx->draw.x1;
		mlx->draw.x1 = mlx->draw.x2;
		mlx->draw.x2 = mlx->draw.temp;
		mlx->draw.temp = mlx->draw.y1;
		mlx->draw.y1 = mlx->draw.y2;
		mlx->draw.y2 = mlx->draw.temp;
	}
	mlx->draw.deltax = ft_fabs(mlx->draw.x2 - mlx->draw.x1);
	mlx->draw.deltay = ft_fabs(mlx->draw.y2 - mlx->draw.y1);
	mlx->draw.parametric_value = 2 * mlx->draw.deltay - mlx->draw.deltax;
	mlx->draw.x = mlx->draw.x1;
	mlx->draw.y = mlx->draw.y1;
	while (mlx->draw.x <= mlx->draw.x2)
	{
		if (check_if_inside(mlx->draw.x, mlx->draw.y))
			image_pixel_put(mlx->draw.color, (int)mlx->draw.x, (int)mlx->draw.y, mlx);
		mlx->draw.x = mlx->draw.x + 1;
		if (mlx->draw.parametric_value >= 0)
			positive_negative_undefined_slope_2(mlx);
		else
			mlx->draw.parametric_value = mlx->draw.parametric_value + 2 * mlx->draw.deltay;
	}
}

static void	negative_slope_2(t_mlx *mlx)
{
	if (mlx->draw.slope >= 1)
		mlx->draw.x = mlx->draw.x + 1;
	else
		mlx->draw.x = mlx->draw.x - 1;
	mlx->draw.parametric_value = mlx->draw.parametric_value + 2 * \
							mlx->draw.deltax - 2 * mlx->draw.deltay;
}

static void	negative_slope_1(t_mlx *mlx)
{
	if (mlx->draw.y1 > mlx->draw.y2)
	{
		mlx->draw.temp = mlx->draw.x1;
		mlx->draw.x1 = mlx->draw.x2;
		mlx->draw.x2 = mlx->draw.temp;
		mlx->draw.temp = mlx->draw.y1;
		mlx->draw.y1 = mlx->draw.y2;
		mlx->draw.y2 = mlx->draw.temp;
	}
	mlx->draw.deltax = ft_fabs(mlx->draw.x2 - mlx->draw.x1);
	mlx->draw.deltay = ft_fabs(mlx->draw.y2 - mlx->draw.y1);
	mlx->draw.parametric_value = 2 * mlx->draw.deltax - mlx->draw.deltay;
	mlx->draw.x = mlx->draw.x1;
	mlx->draw.y = mlx->draw.y1;
	while (mlx->draw.y <= mlx->draw.y2)
	{
		if (check_if_inside(mlx->draw.x, mlx->draw.y))
			image_pixel_put(mlx->draw.color, (int)mlx->draw.x, (int)mlx->draw.y, mlx);
		mlx->draw.y = mlx->draw.y + 1;
		if (mlx->draw.parametric_value >= 0)
			negative_slope_2(mlx);
		else
			mlx->draw.parametric_value = mlx->draw.parametric_value + 2 * mlx->draw.deltax;
	}
}

void	draw_line(t_mlx *mlx)
{
	mlx->draw.deltax = mlx->draw.x2 - mlx->draw.x1;
	mlx->draw.deltay = mlx->draw.y2 - mlx->draw.y1;
	if (mlx->draw.deltax == 0)
		mlx->draw.slope = mlx->draw.deltay;
	else
		mlx->draw.slope = mlx->draw.deltay / mlx->draw.deltax;
	if (ft_fabs(mlx->draw.slope) < 1)
		positive_negative_undefined_slope_1(mlx);
	if (ft_fabs(mlx->draw.slope) >= 1)
		negative_slope_1(mlx);
}
