/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 21:45:41 by raho              #+#    #+#             */
/*   Updated: 2022/08/24 19:55:35 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	create_matrix(t_map *map)
{
	int	index;

	index = 0;
	map->matrix = (int **)malloc(sizeof(int *) * map->height);
	if (map->matrix == NULL)
		exit(1);
	while (index < map->height)
	{
		map->matrix[index] = (int *)malloc(sizeof(int) * map->width);
		if (map->matrix[index] == NULL)
		{
			free_matrix(index, map);
			exit (1);
		}
		ft_bzero((int *)map->matrix[index], map->width);
		index++;
	}
}

void	save_map(char *filename, t_map *map)
{
	int		fd;
	int		ret;
	int		index;
	int		x;
	int		y;
	int		width_counter;
	char	buff[READ_BUFF + 1];

	fd = open_map(filename);
	ret = read(fd, buff, READ_BUFF);
	map->height = 1;
	map->width = 0;
	width_counter = 1;
	index = 0;
	while (ret > 0)
	{
		buff[ret] = '\0';
		while (index < ret)
		{
			if (buff[index] != ' ' && buff[index + 1] == ' ')
				width_counter++;
			if (buff[index] == '\n')
			{
				if (map->width == 0)
					map->width = width_counter;
				/*if (width_counter != map->width)
					exit (1);
				*/
				width_counter = 0;
				map->height++;
			}
			index++;
		}
		ret = read(fd, buff, READ_BUFF);
	}
	close_map(fd, map);
	create_matrix(map);
	fd = open_map(filename);
	ret = read(fd, buff, READ_BUFF);
	index = 0;
	y = 0;
	x = 0;
	while (ret > 0)
	{
		buff[ret] = '\0';
		while (index != ret)
		{
			while (index != ret && buff[index] == ' ')
				index++;
			if (index != ret)
			{
				map->matrix[y][x] = ft_atoi(&buff[index]);
				/*if (map->matrix[y][x] == 0)
				{
					free_matrix(map->height, map);
					ft_putendl_fd("Bad map");
					exit (1);
				}*/
				x++;
				if (x == map->width)
				{
					y++;
					x = 0;
				}
				while (index != ret && buff[index] != ' ')
					index++;
			}
		}
		ret = read(fd, buff, READ_BUFF);
	}
	close_map(fd, map);
}

static void	set_up_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, \
					WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT, "wolf3d");
	mlx->mouse = 1;
}

static void	set_up_player(t_mlx *mlx)
{
	mlx->player.pos_angle = 0;
	mlx->player.pos_x = 200;
	mlx->player.pos_y = 350;
	mlx->player.pos_dx = cos(mlx->player.pos_angle) * 30;
	mlx->player.pos_dy = sin(mlx->player.pos_angle) * 30;
	mlx->player.ray_cpoint_x = 0;
	mlx->player.ray_cpoint_y = 0;
	mlx->player.color = 0xFF0000;
}

static void	set_up_map(t_mlx *mlx)
{
	mlx->map.wall[0].x1 = 0;
	mlx->map.wall[0].y1 = WINDOW_SIZE_HEIGHT;
	mlx->map.wall[0].x2 = 0;
	mlx->map.wall[0].y2 = 0;
	mlx->map.wall[0].color = 0xEC3AAA;
	mlx->map.wall[1].x1 = 0;
	mlx->map.wall[1].y1 = 0;
	mlx->map.wall[1].x2 = WINDOW_SIZE_WIDTH;
	mlx->map.wall[1].y2 = 0;
	mlx->map.wall[1].color = 0xFF64B8;
	mlx->map.wall[2].x1 = WINDOW_SIZE_WIDTH - 1;
	mlx->map.wall[2].y1 = 0;
	mlx->map.wall[2].x2 = WINDOW_SIZE_WIDTH - 1;
	mlx->map.wall[2].y2 = WINDOW_SIZE_HEIGHT;
	mlx->map.wall[2].color = 0xFF98CE;
	mlx->map.wall[3].x1 = 800;
	mlx->map.wall[3].y1 = 300;
	mlx->map.wall[3].x2 = 800;
	mlx->map.wall[3].y2 = 600;
	mlx->map.wall[3].color = 0x00FFFF;
}

void	start(t_mlx *mlx)
{
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, \
					WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT);
	mlx->img.img_addr = mlx_get_data_addr(mlx->img.img_ptr, &mlx->img.bits_per_pixel, \
										&mlx->img.size_line, &mlx->img.endian);
	set_up_player(mlx);
	set_up_map(mlx);
	render_map(mlx);
	render_player(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, \
											mlx->img.img_ptr, 0, 0);
}

int main(int argc, char *argv[])
{
    t_mlx	mlx;

	if (argc == 2)
	{
		initialize_struct(&mlx);
		save_map(argv[1], &mlx.map);
		set_up_mlx(&mlx);
		start(&mlx);
		mlx_hook(mlx.win_ptr, 2, 1L << 0, key_press, (void *)&mlx);
		mlx_hook(mlx.win_ptr, 4, 1L << 2, mouse_click, (void *)&mlx);
		mlx_hook(mlx.win_ptr, 6, 1L << 6, mouse_hover, (void *)&mlx);
		mlx_loop(mlx.mlx_ptr);
	}
	else
		ft_putendl_fd("usage: ./wolf3d map_file", 2);
	return (0);
}
