/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:02:28 by raho              #+#    #+#             */
/*   Updated: 2022/12/20 13:23:21 by raho             ###   ########.fr       */
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
	if (key == MAC_A || key == LINUX_A)
		mlx->player.left = 1;
	if (key == MAC_D || key == LINUX_D)
		mlx->player.right = 1;
	if (key == MAC_W || key == LINUX_W)
		mlx->player.forward = 1;
	if (key == MAC_S || key == LINUX_S)
		mlx->player.back = 1;
	if (key == MAC_SHIFT)
		mlx->player.move_speed = 6;
	if (key == LINUX_ESC || key == MAC_ESC)
		close_program(mlx);
	return (0);
}

int	key_release(int key, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (key == MAC_A)
		mlx->player.left = 0;
	if (key == MAC_D)
		mlx->player.right = 0;
	if (key == MAC_W)
		mlx->player.forward = 0;
	if (key == MAC_S)
		mlx->player.back = 0;
	if (key == MAC_SHIFT)
		mlx->player.move_speed = 4;
	return (0);
}

static void	fix_circle_angle(double *angle)
{
	if (*angle > 360.0)
		*angle -= 360.0;
	else if (*angle < 0.0)
		*angle += 360.0;
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
