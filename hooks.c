/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:02:28 by raho              #+#    #+#             */
/*   Updated: 2022/08/24 20:12:18 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	close_program(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	exit (0);
}

int	key_press(int key, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (key == MAC_A && mlx->mouse == 1)
	{
		mlx->player.pos_angle -= 0.1;
		if (mlx->player.pos_angle < 0)
			mlx->player.pos_angle += 2 * M_PI;
		mlx->player.pos_dx = cos(mlx->player.pos_angle) * 30;
		mlx->player.pos_dy = sin(mlx->player.pos_angle) * 30;
		render_all(mlx);
	}
	if (key == MAC_D && mlx->mouse == 1)
	{
		mlx->player.pos_angle += 0.1;
		if (mlx->player.pos_angle < (2 * M_PI))
			mlx->player.pos_angle -= 2 * M_PI;
		mlx->player.pos_dx = cos(mlx->player.pos_angle) * 30;
		mlx->player.pos_dy = sin(mlx->player.pos_angle) * 30;
		render_all(mlx);
	}	
	if (key == MAC_W)
	{
		mlx->player.pos_x += mlx->player.pos_dx;
		mlx->player.pos_y += mlx->player.pos_dy;
		render_all(mlx);
	}	
	if (key == MAC_S)
	{
		mlx->player.pos_x -= mlx->player.pos_dx;
		mlx->player.pos_y -= mlx->player.pos_dy;
		render_all(mlx);
	}
	if (key == LINUX_ESC || key == MAC_ESC)
		close_program(mlx);
	if (key == MAC_ENTER)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
		mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
		start(mlx);
	}
	return (0);
}

void	render_all(t_mlx *mlx)
{
	erase_map(mlx);
	render_player(mlx);
	render_map(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, \
							mlx->img.img_ptr, 0, 0);
}

void	render_map(t_mlx *mlx)
{
	int	index;

	index = 0;
	while (index < 4)
	{
		mlx->draw.color = mlx->map.wall[index].color;
		mlx->draw.x1 = mlx->map.wall[index].x1;
		mlx->draw.y1 = mlx->map.wall[index].y1;
		mlx->draw.x2 = mlx->map.wall[index].x2;
		mlx->draw.y2 = mlx->map.wall[index].y2;
		draw_line(mlx);
		index++;
	}
}

int		collition_position_check(int index, t_mlx *mlx)
{
	double	x1;
	double	y1;
	double	x2;
	double	y2;
	double	x3;
	double	y3;
	double	x4;
	double	y4;
	double	denominator;
	double	t;
	double	u;
	
	x1 = mlx->map.wall[index].x1;
	y1 = mlx->map.wall[index].y1;
	x2 = mlx->map.wall[index].x2;
	y2 = mlx->map.wall[index].y2;
	x3 = mlx->player.pos_x;
	y3 = mlx->player.pos_y;
	x4 = mlx->player.pos_x + mlx->player.pos_dx;
	y4 = mlx->player.pos_y + mlx->player.pos_dy;
	denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	if (denominator == 0)
		return (0);
	t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denominator;
	u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / denominator;
	if (t > 0 && t < 1 && u > 0)
	{
		mlx->player.ray_cpoint_x = x1 + t * (x2 - x1);
		mlx->player.ray_cpoint_y = y1 + t * (y2 - y1);
		return (1);
	}
	else
		return (0);
}

double	vector_distance(t_mlx *mlx)
{
	double	distance;
	double	temp;

	temp = ((mlx->player.pos_x * mlx->player.pos_x) - \
			(2 * mlx->player.pos_x * mlx->player.ray_cpoint_x) + \
			(mlx->player.ray_cpoint_x * mlx->player.ray_cpoint_x)) + \
			((mlx->player.pos_y * mlx->player.pos_y) - \
			(2 * mlx->player.pos_y * mlx->player.ray_cpoint_y) + \
			(mlx->player.ray_cpoint_y * mlx->player.ray_cpoint_y));
	distance = ft_sqrtd(temp);
	return (distance);
}

int	check_wall_distances(t_mlx *mlx)
{
	int		index;
	double	collision_point_distance;
	double	collision_point_record;

	index = 0;
	collision_point_distance = -1;
	collision_point_record = INFINITY;
	while (index < 4)
	{
		if (collition_position_check(index, mlx) == 1)
		{
			collision_point_distance = vector_distance(mlx);
			if (collision_point_distance < collision_point_record)
			{
				collision_point_record = collision_point_distance;
				mlx->draw.x1 = mlx->player.pos_x;
				mlx->draw.y1 = mlx->player.pos_y;
				mlx->draw.x2 = mlx->player.ray_cpoint_x;
				mlx->draw.y2 = mlx->player.ray_cpoint_y;
			}
		}
		index++;
	}
	if (collision_point_distance != -1)
		return (1);
	else
		return (0);
}

void	render_player(t_mlx *mlx)
{
	if (check_wall_distances(mlx) == 1)
	{
		mlx->draw.color = 0x00FF00;
		draw_line(mlx);
	}
	else
	{
		mlx->draw.color = 0xFF0000;
		mlx->draw.x1 = mlx->player.pos_x;
		mlx->draw.y1 = mlx->player.pos_y;
		mlx->draw.x2 = mlx->player.pos_x + mlx->player.pos_dx;
		mlx->draw.y2 = mlx->player.pos_y + mlx->player.pos_dy;
		draw_line(mlx);
	}
}

int	mouse_click(int button, int x, int y, void *param)
{
	t_mlx	*mlx;

	(void)x;
	(void)y;
	(void)button;
	mlx = (t_mlx *)param;
	if (button == MAC_MOUSE_RIGHT_CLICK)
	{
		mlx->map.wall[3].x1 = x;
		mlx->map.wall[3].y1 = y;
		mlx->map.wall[3].x2 = x;
		mlx->map.wall[3].y2 = y + 300;
		render_all(mlx);
	}
	if (button == MAC_MOUSE_LEFT_CLICK)
	{
		if (mlx->mouse == 1)
			mlx->mouse = 0;
		else
			mlx->mouse = 1;
	}
	return (0);
}

int	mouse_hover(int x, int y, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if ((x >= 0 && x < WINDOW_SIZE_WIDTH) && (y >= 0 && y < WINDOW_SIZE_HEIGHT) && mlx->mouse == 0)
	{
		mlx->player.pos_dx = x - mlx->player.pos_x;
		mlx->player.pos_dy = y - mlx->player.pos_y;
		render_all(mlx);
	}
	return (0);
}
