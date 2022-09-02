/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:02:28 by raho              #+#    #+#             */
/*   Updated: 2022/09/02 06:25:48 by raho             ###   ########.fr       */
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
	}
	if (key == MAC_D && mlx->mouse == 1)
	{
		mlx->player.pos_angle += 0.1;
		if (mlx->player.pos_angle < (2 * M_PI))
			mlx->player.pos_angle -= 2 * M_PI;
		mlx->player.pos_dx = cos(mlx->player.pos_angle) * 30;
		mlx->player.pos_dy = sin(mlx->player.pos_angle) * 30;
	}	
	if (key == MAC_W)
	{
		mlx->player.pos_x += mlx->player.pos_dx;
		mlx->player.pos_y += mlx->player.pos_dy;
	}	
	if (key == MAC_S)
	{
		mlx->player.pos_x -= mlx->player.pos_dx;
		mlx->player.pos_y -= mlx->player.pos_dy;
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

int	render_all(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	erase_img(&mlx->img);
	render_map(mlx);
	render_player(&mlx->player, &mlx->draw, &mlx->img);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, \
											mlx->img.img_ptr, 0, 0);
	return (0);
}

int	mouse_click(int button, int x, int y, void *param)
{
	t_mlx	*mlx;

	(void)x;
	(void)y;
	(void)button;
	mlx = (t_mlx *)param;
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
	if ((x >= 0 && x < WINDOW_SIZE_WIDTH) && (y >= 0 && y < WINDOW_SIZE_HEIGHT) \
		&& mlx->mouse == 0)
	{
		mlx->player.pos_dx = x - mlx->player.pos_x;
		mlx->player.pos_dy = y - mlx->player.pos_y;
	}
	return (0);
}
