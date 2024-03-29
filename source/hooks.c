/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:02:28 by raho              #+#    #+#             */
/*   Updated: 2022/12/21 15:07:07 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	close_program(t_mlx *mlx)
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
	if (key == MAC_LEFT || key == LINUX_LEFT)
		mlx->player.left = 1;
	if (key == MAC_RIGHT || key == LINUX_RIGHT)
		mlx->player.right = 1;
	if (key == MAC_FORWARD || key == LINUX_FORWARD)
		mlx->player.forward = 1;
	if (key == MAC_BACK || key == LINUX_BACK)
		mlx->player.back = 1;
	if (key == MAC_SHIFT || key == LINUX_SHIFT)
	{
		mlx->player.move_speed = MOVE_SPEED * 2;
		mlx->player.turn_speed = TURN_SPEED * 2;
	}
	if (key == MAC_ESC || key == LINUX_ESC)
		close_program(mlx);
	return (0);
}

int	key_release(int key, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (key == MAC_LEFT || key == LINUX_LEFT)
		mlx->player.left = 0;
	if (key == MAC_RIGHT || key == LINUX_RIGHT)
		mlx->player.right = 0;
	if (key == MAC_FORWARD || key == LINUX_FORWARD)
		mlx->player.forward = 0;
	if (key == MAC_BACK || key == LINUX_BACK)
		mlx->player.back = 0;
	if (key == MAC_SHIFT || key == LINUX_SHIFT)
	{
		mlx->player.move_speed = MOVE_SPEED;
		mlx->player.turn_speed = TURN_SPEED;
	}
	return (0);
}

static void	fix_circle_angle(float *angle)
{
	if (*angle > 360)
		*angle -= 360;
	else if (*angle < 0)
		*angle += 360;
}

int	render_all(void *param)
{
	t_mlx		*mlx;
	int			ray_nbr;

	mlx = (t_mlx *)param;
	add_movement(mlx);
	mlx->raycast.ray_angle = mlx->player.pos_angle + (FOV / 2);
	fix_circle_angle(&mlx->raycast.ray_angle);
	ray_nbr = 0;
	while (ray_nbr < WINDOW_WIDTH)
	{
		raycast(mlx);
		if (mlx->raycast.closest_coll_dist > 0)
			draw_column(mlx, ray_nbr);
		mlx->raycast.ray_angle -= mlx->raycast.degrees_per_ray;
		fix_circle_angle(&mlx->raycast.ray_angle);
		ray_nbr++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, \
											mlx->img.img_ptr, 0, 0);
	return (0);
}
