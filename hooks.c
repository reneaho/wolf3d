/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:02:28 by raho              #+#    #+#             */
/*   Updated: 2022/12/17 07:40:06 by raho             ###   ########.fr       */
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
	if (key == MAC_A || LINUX_A)
		mlx->player.left = 1;
	if (key == MAC_D || LINUX_D)
		mlx->player.right = 1;
	if (key == MAC_W || LINUX_W)
		mlx->player.forward = 1;
	if (key == MAC_S || LINUX_S)
		mlx->player.back = 1;
	if (key == MAC_SHIFT)
		mlx->player.move_speed = 6;
	if (key == LINUX_ESC || key == MAC_ESC)
		close_program(mlx);
	if (key == MAC_ENTER || LINUX_ENTER)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
		mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
		init_structs(mlx);
	}
	return (0);
}

int	key_release(int key, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (key == MAC_A || LINUX_A)
		mlx->player.left = 0;
	if (key == MAC_D || LINUX_D)
		mlx->player.right = 0;
	if (key == MAC_W|| LINUX_W)
		mlx->player.forward = 0;
	if (key == MAC_S || LINUX_S)
		mlx->player.back = 0;
	if (key == MAC_SHIFT)
		mlx->player.move_speed = 4;
	return (0);
}

void	limit_collision(t_mlx *mlx)
{
	int	x_offset;
	int	y_offset;
	int	player_pos_x_in_square;
	int	player_pos_x_in_square_plus_offset;
	int	player_pos_x_in_square_minus_offset;
	int	player_pos_y_in_square;
	int	player_pos_y_in_square_plus_offset;
	int	player_pos_y_in_square_minus_offset;


	x_offset = 0;
	y_offset = 0;
	
	if (mlx->player.dir_x < 0)
		x_offset = -15;
	else
		x_offset = 15;
	if (mlx->player.dir_y < 0)
		y_offset = -15;
	else
		y_offset = 15;

	player_pos_x_in_square = mlx->player.pos_x / 64.0;
	player_pos_x_in_square_plus_offset = (mlx->player.pos_x + x_offset) / 64.0;
	player_pos_x_in_square_minus_offset = (mlx->player.pos_x - x_offset) / 64.0;
	
	player_pos_y_in_square = mlx->player.pos_y / 64.0;
	player_pos_y_in_square_plus_offset = (mlx->player.pos_y + y_offset) / 64.0;
	player_pos_y_in_square_minus_offset = (mlx->player.pos_y - y_offset) / 64.0;
	
	if (mlx->player.forward == 1)
	{
		if (mlx->map.matrix[player_pos_y_in_square][player_pos_x_in_square_plus_offset] == 0)
			mlx->player.pos_x += mlx->player.dir_x * mlx->player.move_speed;
		if (mlx->map.matrix[player_pos_y_in_square_plus_offset][player_pos_x_in_square] == 0)
			mlx->player.pos_y += mlx->player.dir_y * mlx->player.move_speed;
	}
	if (mlx->player.back == 1)
	{
		if (mlx->map.matrix[player_pos_y_in_square][player_pos_x_in_square_minus_offset] == 0)
			mlx->player.pos_x -= mlx->player.dir_x * mlx->player.move_speed;
		if (mlx->map.matrix[player_pos_y_in_square_minus_offset][player_pos_x_in_square] == 0)
			mlx->player.pos_y -= mlx->player.dir_y * mlx->player.move_speed;
	}
}

void	add_movement(t_mlx *mlx)
{
	if (mlx->player.left == 1)
	{
		mlx->player.pos_angle += TURN_SPEED;
		if (mlx->player.pos_angle >= 360)
			mlx->player.pos_angle -= 360;
		mlx->player.dir_x = cos(ft_deg_to_rad(mlx->player.pos_angle));
		mlx->player.dir_y = -sin(ft_deg_to_rad(mlx->player.pos_angle));
	}
	if (mlx->player.right == 1)
	{
		mlx->player.pos_angle -= TURN_SPEED;
		if (mlx->player.pos_angle < 0)
			mlx->player.pos_angle += 360;
		mlx->player.dir_x = cos(ft_deg_to_rad(mlx->player.pos_angle));
		mlx->player.dir_y = -sin(ft_deg_to_rad(mlx->player.pos_angle));
	}
	if (mlx->player.forward == 1 || mlx->player.back == 1)
		limit_collision(mlx);
}

void fps_counter(void)
{
	static unsigned int	old_time;
	unsigned int		current_time;
	static unsigned int	fps_counter;

	current_time = clock();
	if (old_time > current_time)
		fps_counter++;
	else
	{
		printf("fps: %d\n", fps_counter);
		old_time = current_time + CLOCKS_PER_SEC;
		fps_counter = 0;
	}
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
	//fps_counter();
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, \
											mlx->img.img_ptr, 0, 0);
	return (0);
}
