/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 21:45:41 by raho              #+#    #+#             */
/*   Updated: 2022/09/02 06:22:10 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	print_map_matrix(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			ft_putnbr(map->matrix[y][x]);
			x++;
		}
		ft_putchar('\n');
		y++;
	}
}

void	start(t_mlx *mlx)
{
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, \
					WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT);
	mlx->img.img_addr = mlx_get_data_addr(mlx->img.img_ptr, \
						&mlx->img.bits_per_pixel, \
						&mlx->img.size_line, &mlx->img.endian);
	print_map_matrix(&mlx->map);
}

int	main(int argc, char *argv[])
{
	t_mlx	mlx;

	if (argc == 2)
	{
		set_up_structs(&mlx);
		set_up_structs(&mlx);
		save_map(argv[1], &mlx.map);
		start(&mlx);
		mlx_hook(mlx.win_ptr, 2, 1L << 0, key_press, (void *)&mlx);
		mlx_hook(mlx.win_ptr, 4, 1L << 2, mouse_click, (void *)&mlx);
		mlx_hook(mlx.win_ptr, 6, 1L << 6, mouse_hover, (void *)&mlx);
		mlx_loop_hook(mlx.mlx_ptr, render_all, (void *)&mlx);
		mlx_loop(mlx.mlx_ptr);
	}
	else
		ft_putendl_fd("usage: ./wolf3d map_file", 2);
	return (0);
}
