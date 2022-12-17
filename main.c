/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 21:45:41 by raho              #+#    #+#             */
/*   Updated: 2022/12/17 07:35:39 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_structs(t_mlx *mlx)
{
	static int	restart = 0;

	if (restart == 0)
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
		restart = 1;
	}

	mlx->player.move_speed = 4;
	mlx->raycast.dist_to_proj_plane = (double)(WINDOW_WIDTH / 2) / tan(ft_deg_to_rad(FOV / 2));
	mlx->raycast.degrees_per_column = (double)WINDOW_WIDTH / (double)FOV;
	mlx->raycast.degrees_per_ray = (double)FOV / (double)WINDOW_WIDTH;
}

int	find_player_starting_position(t_mlx *mlx)
{
	int	x;
	int	y;

	/* Find a square for the player to start from - that's not a wall */

	y = 1;
	while (y < mlx->map.height)
	{
		x = 1;
		while (x < mlx->map.height)
		{
			if (mlx->map.matrix[y][x] == 0)
			{
				/* Find the direction in which the next wall-less square is */
				
				if (mlx->map.matrix[y][x + 1] == 0)
					mlx->player.pos_angle = 0;
				else if (mlx->map.matrix[y + 1][x] == 0)
					mlx->player.pos_angle = 270;
				else
					mlx->player.pos_angle = 180;
				
				/* Set up the player's starting position and get out of the loop */
				mlx->player.pos_x = (double)SQUARE_SIZE * (x + 1) - ((double)SQUARE_SIZE / 2.0);
				mlx->player.pos_y = (double)SQUARE_SIZE * (y + 1) - ((double)SQUARE_SIZE / 2.0);
				mlx->player.dir_x = cos(ft_deg_to_rad(mlx->player.pos_angle)); // * RAY_LENGTH to see the ray direction
				mlx->player.dir_y = -sin(ft_deg_to_rad(mlx->player.pos_angle)); // * RAY_LENGTH to see the ray direction
				return (0);
			}
			x++;
		}
		y++;
	}
	return (-1);
}

/* 1st pixel wrong */

void	force_player_starting_point(t_mlx *mlx)
{
	mlx->player.pos_angle = 270.0;
	mlx->player.pos_x = 110.0;
	mlx->player.pos_y = 110.0;
	mlx->player.dir_x = cos(ft_deg_to_rad(mlx->player.pos_angle)); // * RAY_LENGTH to see the ray direction
	mlx->player.dir_y = -sin(ft_deg_to_rad(mlx->player.pos_angle)); // * RAY_LENGTH to see the ray direction
}

/* guide starting point */
/*
void	force_player_starting_point(t_mlx *mlx)
{
	mlx->player.pos_angle = 60.0;
	mlx->player.pos_x = 342.0;
	mlx->player.pos_y = 227.0;
	mlx->player.dir_x = cos(ft_deg_to_rad(mlx->player.pos_angle)); // * RAY_LENGTH to see the ray direction
	mlx->player.dir_y = -sin(ft_deg_to_rad(mlx->player.pos_angle)); // * RAY_LENGTH to see the ray direction
}
*/


int	main(int argc, char *argv[])
{
	t_mlx	mlx;

	if (argc == 2)
	{
		init_structs(&mlx);
		save_map(argv[1], &mlx.map);
		/*
		if (find_player_start_position(&mlx) == -1)
		{
			ft_putendl_fd("no valid starting point for the player", 2);
			exit (1);
		}
		*/
		force_player_starting_point(&mlx);
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
