/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:57:27 by raho              #+#    #+#             */
/*   Updated: 2023/02/21 15:25:55 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# define WINDOW_WIDTH 1200
# define WINDOW_HEIGHT 900
# define SQUARE_SIZE 64
# define FOV 40
# define RAY_LENGTH 3
# define MOVE_SPEED 3
# define TURN_SPEED 1
# define DEGREE	0.0174533 // one degree in radians
# define NORTH 1
# define EAST 2
# define SOUTH 3
# define WEST 4

# define LEFT 123
# define RIGHT 124
# define FORWARD 126
# define BACK 125
# define SHIFT 257
# define ESC 53

# define MOSS_GREEN 0x414129
# define SOFT_SKY_BLUE 0x4C7CAD

# define EC_OPEN -21
# define EC_GNL -22
# define EC_CLOSE -23
# define EC_MALLOC -24
# define EC_BADMAP -25

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>

typedef struct s_pointf
{
	float	x;
	float	y;
}	t_pointf;

typedef struct s_map
{
	int		**matrix;
	int		width;
	int		height;
}	t_map;

typedef struct s_collision
{
	int	square_pos_x;
	int	square_pos_x_plus_offset;
	int	square_pos_x_minus_offset;
	int	square_pos_y;
	int	square_pos_y_plus_offset;
	int	square_pos_y_minus_offset;
}	t_collision;

typedef struct s_player
{
	t_collision	collision;
	float		pos_angle;
	float		pos_x;
	float		pos_y;
	float		dir_x;
	float		dir_y;
	int			move_speed;
	int			turn_speed;
	int			compass;
	int			left;
	int			right;
	int			forward;
	int			back;
}	t_player;

typedef struct s_raycast
{
	float	ray_angle;
	float	ray_x;
	float	ray_y;
	int		map_x;
	int		map_y;
	float	offset_x;
	float	offset_y;
	float	dist_to_proj_plane;
	float	degrees_per_column;
	float	degrees_per_ray;
	float	hor_coll_point_x;
	float	ver_coll_point_y;
	float	closest_coll_dist;
	int		projected_slice_height;
	int		wall_texture_xoffset;
	int		wall_texture_yoffset;
	float	wall_texture_yincrement;
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

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_map		map;
	t_player	player;
	t_raycast	raycast;
	t_texture	texture[4];
}	t_mlx;

void	init_textures(t_mlx *mlx);

void	read_map(t_map *map, char *filename);
void	save_map(t_map *map, char *filename);
void	validate_map(t_map *map);

int		render_all(void *param);

int		key_press(int key, void *param);
int		key_release(int key, void *param);

void	add_movement(t_mlx *mlx);

void	raycast(t_mlx *mlx);
float	ray_collision_distance(t_player *player, t_pointf collision);

int		find_hor_coll_point(t_mlx *mlx);
float	calc_hor_coll_dist(t_mlx *mlx);
void	save_horizontal(t_mlx *mlx, float hor_coll_dist);

int		find_ver_coll_point(t_mlx *mlx);
float	calc_ver_coll_dist(t_mlx *mlx);
void	save_vertical(t_mlx *mlx, float ver_coll_dist);

void	draw_column(t_mlx *mlx, int ray_nbr);

void	errors(int error_code);
void	errors_fd(int error_code, int fd);
int		close_program(t_mlx *mlx);

#endif
