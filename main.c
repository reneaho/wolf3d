/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 21:45:41 by raho              #+#    #+#             */
/*   Updated: 2022/12/21 14:22:52 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	init_structs(t_mlx *mlx)
{
	ft_bzero(mlx, sizeof(t_mlx));
	mlx->mlx_ptr = mlx_init();
	if (mlx->mlx_ptr == NULL)
		exit (1);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, \
					WINDOW_WIDTH, WINDOW_HEIGHT, "wolf3d");
	if (mlx->win_ptr == NULL)
		exit (1);
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, \
				WINDOW_WIDTH, WINDOW_WIDTH);
	if (mlx->img.img_ptr == NULL)
		exit (1);
	mlx->img.img_addr = mlx_get_data_addr(mlx->img.img_ptr, \
						&mlx->img.bits_per_pixel, \
						&mlx->img.size_line, &mlx->img.endian);
	if (mlx->img.img_addr == NULL)
		exit (1);
	init_textures(mlx);
	mlx->player.move_speed = MOVE_SPEED;
	mlx->player.turn_speed = TURN_SPEED;
	mlx->raycast.dist_to_proj_plane = (double)(WINDOW_WIDTH / 2) / \
										tan(ft_deg_to_rad(FOV / 2));
	mlx->raycast.degrees_per_column = (double)WINDOW_WIDTH / (double)FOV;
	mlx->raycast.degrees_per_ray = (double)FOV / (double)WINDOW_WIDTH;
}

static void	save_player_pos(t_mlx *mlx, int x, int y)
{
	if (mlx->map.matrix[y][x + 1] == 0)
		mlx->player.pos_angle = 0;
	else if (mlx->map.matrix[y + 1][x] == 0)
		mlx->player.pos_angle = 270;
	else
		mlx->player.pos_angle = 180;
	mlx->player.pos_x = (double)SQUARE_SIZE * (x + 1) - \
						((double)SQUARE_SIZE / 2.0);
	mlx->player.pos_y = (double)SQUARE_SIZE * (y + 1) - \
						((double)SQUARE_SIZE / 2.0);
	mlx->player.dir_x = cos(ft_deg_to_rad(mlx->player.pos_angle));
	mlx->player.dir_y = -sin(ft_deg_to_rad(mlx->player.pos_angle));
}

static int	find_player_start_position(t_mlx *mlx)
{
	int	x;
	int	y;

	y = 1;
	while (y < mlx->map.height)
	{
		x = 1;
		while (x < mlx->map.width)
		{
			if (mlx->map.matrix[y][x] == 0)
			{
				save_player_pos(mlx, x, y);
				return (0);
			}
			x++;
		}
		y++;
	}
	return (-1);
}

int	main(int argc, char *argv[])
{
	t_mlx	mlx;

	if (argc == 2)
	{
		init_structs(&mlx);
		read_map(&mlx.map, argv[1]);
		save_map(&mlx.map, argv[1]);
		validate_map(&mlx.map);
		if (find_player_start_position(&mlx) == -1)
		{
			ft_putendl_fd("no valid starting point for the player", 2);
			exit (1);
		}
		mlx_hook(mlx.win_ptr, 2, 1L << 0, key_press, (void *)&mlx);
		mlx_hook(mlx.win_ptr, 3, 1L << 1, key_release, (void *)&mlx);
		mlx_hook(mlx.win_ptr, 17, 0, close_program, (void *)&mlx);
		mlx_loop_hook(mlx.mlx_ptr, render_all, (void *)&mlx);
		mlx_loop(mlx.mlx_ptr);
	}
	else
		ft_putendl_fd("usage: ./wolf3d map_file", 2);
	return (0);
}
