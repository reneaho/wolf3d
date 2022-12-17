/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:25:14 by raho              #+#    #+#             */
/*   Updated: 2022/09/12 18:52:52 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	image_pixel_put(t_draw *draw, t_img *img)
{
	char	*pixel;

	if ((draw->x >= 0 && draw->x <= img->width) && \
		(draw->y >= 0 && draw->y <= img->height))
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
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			pixel = img->img_addr + (y * img->size_line) + \
						(x * (img->bits_per_pixel / 8));
			*(int *)pixel = 0;
			x++;
		}
		y++;
	}
}
