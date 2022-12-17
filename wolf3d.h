/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:57:27 by raho              #+#    #+#             */
/*   Updated: 2022/12/17 07:47:28 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# define READ_BUFF 500
# define WINDOW_WIDTH 1200
# define WINDOW_HEIGHT 900
# define SQUARE_SIZE 64
# define FOV 60
# define RAY_LENGTH 3
# define TURN_SPEED 3
# define DEGREE	0.0174533 // one degree in radians
# define LINUX_W 119
# define LINUX_A 97
# define LINUX_S 115
# define LINUX_D 100
# define LINUX_LEFT 65361
# define LINUX_UP 65362
# define LINUX_RIGHT 65363
# define LINUX_DOWN 65364
# define LINUX_ENTER 65293
# define LINUX_ESC 65307
# define MAC_W 13
# define MAC_A 0
# define MAC_S 1
# define MAC_D 2
# define MAC_LEFT 123
# define MAC_UP 126
# define MAC_RIGHT 124
# define MAC_DOWN 125
# define MAC_SHIFT 257
# define MAC_ENTER 36
# define MAC_ESC 53
# define MOSS_GREEN 0x414129;
# define SOFT_SKY_BLUE 0x4C7CAD;
# define NORTH 1
# define EAST 2
# define SOUTH 3
# define WEST 4

# include "libft/libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <time.h>

typedef struct s_draw
{
	double	x;
	double	y;
	double	x1;
	double	y1;
	double	x2;
	double	y2;
	double	deltax;
	double	deltay;
	double	slope;
	double	parametric_value;
	double	temp;
	int		color;
}	t_draw;

typedef struct s_wall
{
	double	x1;
	double	y1;
	double	x2;
	double	y2;
	int		color;
}	t_wall;

typedef struct s_map
{
	int		**matrix;
	int		width;
	int		width_counter;
	int		height;
	int		wall_w;
	int		wall_h;
	t_wall	wall[4];
}	t_map;

typedef struct s_player
{
	double	pos_angle;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	int		move_speed;
	int		compass;
	int		left;
	int		right;
	int		forward;
	int		back;
}	t_player;

typedef struct s_raycast
{
	double	ray_angle;
	double	ray_x;
	double	ray_y;
	int		map_x;
	int		map_y;
	double	offset_x;
	double	offset_y;
	double	dist_to_proj_plane;
	double	degrees_per_column;
	double	degrees_per_ray;
	int		projected_slice_height;
	double	hor_coll_point_x;
	double	ver_coll_point_y;
	double	closest_coll_dist;
	int		wall_texture_offset;
}	t_raycast;

typedef struct s_img
{
	void		*img_ptr;
	char		*img_addr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int			height;
	int			width;
}	t_img;

typedef struct s_texture
{
	char	**texture;
	int		width;
	int		height;
	int		color;
	void	*img_ptr;
	char	*img_addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		img_height;
	int		img_width;
	
}	t_texture;

typedef struct s_keys
{

}	t_keys;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_map		map;
	t_draw		draw;
	t_player	player;
	t_raycast	raycast;
	t_texture	texture[4];
	t_keys		keys;
}	t_mlx;

void	init_textures(t_mlx *mlx);

void	init_structs(t_mlx *mlx);

int		open_map(char *filename);

void	close_map(int fd, t_map *map);

void	save_map(char *filename, t_map *map);

int		render_all(void *param);

void	raycast(t_mlx *mlx);

int		key_press(int key, void *param);

int		close_program(t_mlx *mlx);

int		key_release(int key, void *param);

void	draw_column(int ray_nbr, t_mlx *mlx);

double	ray_collision_distance(t_player *player, double coll_x, double coll_y);

int		find_hor_coll_point(t_mlx *mlx);
double	calc_hor_coll_dist(t_mlx *mlx);
void	save_horizontal(t_mlx *mlx, double hor_coll_dist);

int		find_ver_coll_point(t_mlx *mlx);
double	calc_ver_coll_dist(t_mlx *mlx);
void	save_vertical(t_mlx *mlx, double ver_coll_dist);


#endif
