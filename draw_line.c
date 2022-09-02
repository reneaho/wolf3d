/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:05:05 by raho              #+#    #+#             */
/*   Updated: 2022/09/02 06:21:48 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	positive_negative_undefined_slope_2(t_draw *draw)
{
	if (draw->slope < 1 && draw->y1 < draw->y2)
		draw->y = draw->y + 1;
	else
		draw->y = draw->y - 1;
	draw->parametric_value = draw->parametric_value + 2 * \
							draw->deltay - 2 * draw->deltax;
}

static void	positive_negative_undefined_slope_1(t_draw *draw, t_img *img)
{
	if (draw->x1 > draw->x2)
	{
		draw->temp = draw->x1;
		draw->x1 = draw->x2;
		draw->x2 = draw->temp;
		draw->temp = draw->y1;
		draw->y1 = draw->y2;
		draw->y2 = draw->temp;
	}
	draw->deltax = ft_fabs(draw->x2 - draw->x1);
	draw->deltay = ft_fabs(draw->y2 - draw->y1);
	draw->parametric_value = 2 * draw->deltay - draw->deltax;
	draw->x = draw->x1;
	draw->y = draw->y1;
	while (draw->x <= draw->x2)
	{
		image_pixel_put(draw, img);
		draw->x = draw->x + 1;
		if (draw->parametric_value >= 0)
			positive_negative_undefined_slope_2(draw);
		else
			draw->parametric_value = draw->parametric_value + 2 * draw->deltay;
	}
}

static void	negative_slope_2(t_draw *draw)
{
	if (draw->slope >= 1)
		draw->x = draw->x + 1;
	else
		draw->x = draw->x - 1;
	draw->parametric_value = draw->parametric_value + 2 * \
							draw->deltax - 2 * draw->deltay;
}

static void	negative_slope_1(t_draw *draw, t_img *img)
{
	if (draw->y1 > draw->y2)
	{
		draw->temp = draw->x1;
		draw->x1 = draw->x2;
		draw->x2 = draw->temp;
		draw->temp = draw->y1;
		draw->y1 = draw->y2;
		draw->y2 = draw->temp;
	}
	draw->deltax = ft_fabs(draw->x2 - draw->x1);
	draw->deltay = ft_fabs(draw->y2 - draw->y1);
	draw->parametric_value = 2 * draw->deltax - draw->deltay;
	draw->x = draw->x1;
	draw->y = draw->y1;
	while (draw->y <= draw->y2)
	{
		image_pixel_put(draw, img);
		draw->y = draw->y + 1;
		if (draw->parametric_value >= 0)
			negative_slope_2(draw);
		else
			draw->parametric_value = draw->parametric_value + 2 * draw->deltax;
	}
}

void	draw_line(t_draw *draw, t_img *img)
{
	draw->deltax = draw->x2 - draw->x1;
	draw->deltay = draw->y2 - draw->y1;
	if (draw->deltax == 0)
		draw->slope = draw->deltay;
	else
		draw->slope = draw->deltay / draw->deltax;
	if (ft_fabs(draw->slope) < 1)
		positive_negative_undefined_slope_1(draw, img);
	if (ft_fabs(draw->slope) >= 1)
		negative_slope_1(draw, img);
}
