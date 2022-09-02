/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 06:06:16 by raho              #+#    #+#             */
/*   Updated: 2022/09/02 06:24:36 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_square(int x, int y, t_draw *draw, t_img *img)
{
	draw->x1 = x;
	draw->y1 = y;
	draw->x2 = x + SQUARE_SIZE;
	draw->y2 = y;
	draw_line(draw, img);
	draw->x1 = x + SQUARE_SIZE;
	draw->y1 = y;
	draw->x2 = x + SQUARE_SIZE;
	draw->y2 = y + SQUARE_SIZE;
	draw_line(draw, img);
	draw->x1 = x + SQUARE_SIZE;
	draw->y1 = y + SQUARE_SIZE;
	draw->x2 = x;
	draw->y2 = y + SQUARE_SIZE;
	draw_line(draw, img);
	draw->x1 = x;
	draw->y1 = y + SQUARE_SIZE;
	draw->x2 = x;
	draw->y2 = y;
	draw_line(draw, img);
}

void	set_wall_color(int wall_value, t_draw *draw)
{
	if (wall_value == 1)
		draw->color = LIGHT_BLUE;
	if (wall_value == 2)
		draw->color = LIGHT_GREEN;
	if (wall_value == 3)
		draw->color = LIGHT_ORANGE;
}

void	render_map(t_mlx *mlx)
{
	int	x;
	int	y;
	int	x1;
	int	y1;

	y = 0;
	while (y < mlx->map.height)
	{
		x = 0;
		while (x < mlx->map.width)
		{
			if (mlx->map.matrix[y][x] != 0)
			{
				set_wall_color(mlx->map.matrix[y][x], &mlx->draw);
				x1 = x * SQUARE_SIZE;
				y1 = y * SQUARE_SIZE;
				draw_square(x1, y1, &mlx->draw, &mlx->img);
			}
			x++;
		}
		y++;
	}
}

void	render_player(t_player *player, t_draw *draw, t_img *img)
{
	draw->color = player->color;
	draw->x1 = player->pos_x;
	draw->y1 = player->pos_y;
	draw->x2 = player->pos_x + player->pos_dx;
	draw->y2 = player->pos_y + player->pos_dy;
	draw_line(draw, img);
}
