/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:57:27 by raho              #+#    #+#             */
/*   Updated: 2022/09/02 06:32:08 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# define READ_BUFF 500
# define WINDOW_SIZE_WIDTH 1010
# define WINDOW_SIZE_HEIGHT 1010
# define SQUARE_SIZE 100
/* # define SQUARE_HEIGHT */
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
# define LINUX_MOUSE_LEFT_CLICK 1
# define LINUX_MOUSE_RIGHT_CLICK 2
# define MAC_W 13
# define MAC_A 0
# define MAC_S 1
# define MAC_D 2
# define MAC_LEFT 123
# define MAC_UP 126
# define MAC_RIGHT 124
# define MAC_DOWN 125
# define MAC_ENTER 36
# define MAC_ESC 53
# define MAC_MOUSE_LEFT_CLICK 1
# define MAC_MOUSE_RIGHT_CLICK 2
# define LIGHT_BLUE 0x00B2CA
# define LIGHT_GREEN 0x7DCFB6
# define LIGHT_ORANGE 0xF79256
# define LIGHT_PINK 0xFFBAD2

# include "libft/libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>

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
}		t_draw;

typedef struct s_wall
{
	double	x1;
	double	y1;
	double	x2;
	double	y2;
	int		color;
}		t_wall;

typedef struct s_map
{
	int		**matrix;
	int		width;
	int		width_counter;
	int		height;
	int		wall_w;
	int		wall_h;
	t_wall	wall[4];
}		t_map;

typedef struct s_player
{
	double	pos_angle;
	double	pos_x;
	double	pos_y;
	double	pos_dx;
	double	pos_dy;
	double	collpoint_distance;
	double	collpoint_record;
	double	ray_cpoint_x;
	double	ray_cpoint_y;
	int		color;
}		t_player;

typedef struct s_img
{
	void		*img_ptr;
	char		*img_addr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
}		t_img;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			mouse;
	t_img		img;
	t_map		map;
	t_draw		draw;
	t_player	player;
}		t_mlx;

void	set_up_structs(t_mlx *mlx);

int		open_map(char *filename);

void	close_map(int fd, t_map *map);

void	save_map(char *filename, t_map *map);

void	start(t_mlx *mlx);

void	draw_line(t_draw *draw, t_img *img);

int		render_all(void *param);

void	render_player(t_player *player, t_draw *draw, t_img *img);

void	render_map(t_mlx *mlx);

void	image_pixel_put(t_draw *draw, t_img *img);

void	erase_img(t_img *img);

int		key_press(int key, void *param);

int		mouse_click(int mouse_button, int x, int y, void *param);

int		mouse_hover(int x, int y, void *param);

void	free_matrix(int height, t_map *map);

double	scale_value_x(int x, double newmin, double newmax);

double	scale_value_y(int y, double newmin, double newmax);

#endif
