/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:25:14 by raho              #+#    #+#             */
/*   Updated: 2022/09/02 06:34:15 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	image_pixel_put(t_draw *draw, t_img *img)
{
	char	*pixel;

	if ((draw->x >= 0 && draw->x < WINDOW_SIZE_WIDTH) && \
		(draw->y >= 0 && draw->y < WINDOW_SIZE_HEIGHT))
	{
		pixel = img->img_addr + (((int)draw->y * img->size_line) + \
									((int)draw->x * (img->bits_per_pixel / 8)));
		*(int *)pixel = draw->color;
	}
}

void	erase_img(t_img *img)
{
	int		x;
	int		y;
	char	*pixel;

	y = 0;
	while (y < WINDOW_SIZE_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_SIZE_WIDTH)
		{
			pixel = img->img_addr + (y * img->size_line) + \
						(x * (img->bits_per_pixel / 8));
			*(int *)pixel = 0;
			x++;
		}
		y++;
	}
}
