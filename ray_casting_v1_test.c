/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_v1_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:35:05 by raho              #+#    #+#             */
/*   Updated: 2022/09/21 19:03:03 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	breakpoint(void)
{
	
}

double	ray_collision_distance(t_player *player, double coll_x, double coll_y)
{
	double	distance;
	double	temp;

	temp = ((player->pos_x * player->pos_x) - \
			(2.0 * player->pos_x * coll_x) + \
			(coll_x * coll_x)) + \
			((player->pos_y * player->pos_y) - \
			(2.0 * player->pos_y * coll_y) + \
			(coll_y * coll_y));
	distance = ft_sqrtd(temp);
	return (distance);
}

double	ray_collision_distance_angles(t_mlx *mlx)
{
	double	temp;

	temp = cos(ft_deg_to_rad(mlx->player.ray_angle)) * (mlx->player.ray_x - mlx->player.pos_x) - \
			sin(ft_deg_to_rad(mlx->player.ray_angle)) * (mlx->player.ray_y - mlx->player.pos_y);
	return (temp);
}

/* Converts a 2 character long hex code to integer form */

int	convert_hex_color_to_int(char *hexcolor)
{
	int	index;
	int	color;
	int	base;

	base = 1;
	color = 0;
	index = 1;
	while (index >= 0)
	{
		if (hexcolor[index] >= '0' && hexcolor[index] <= '9')
		{
			color += (int)(hexcolor[index] - 48) * base;
			base = base * 16;
		}
		else if (hexcolor[index] >= 'A' && hexcolor[index] <= 'F')
		{
			color += (int)(hexcolor[index] - 55) * base;
			base = base * 16;
		}
		index--;
	}
	return (color);
}

int	choose_texture(int scaled_starting_point, t_mlx *mlx)
{
	int	rgb;
	int	color_x;
	int	color_y;
	int	texture_x;
	int	texture_y;
	char	*texture_pos;
	int	alpha;
	int	red;
	int	green;
	int	blue;

	alpha = 0;

	/* Texture file has pictures in the form of 128x64 per picture, 5 pictures per row. */
	/* Pixel is represented by 2 chars that will tell the correct color for the pixel. */
	/* First character needs to be skipped and the pictures start from the row 211. */
	/* Color code needs to be looked up from the rows 5-209. */
	
	/* First checking from which direction did the ray hit the wall and saving the desired texture's starting address. */
	
	if (mlx->player.compass == 1) // North/Up
	{
		texture_x = 1 + (mlx->player.wall_texture_offset * 2);
		texture_y = 210 + scaled_starting_point;
	}
	if (mlx->player.compass == 2) // East/Right
	{
		texture_x = 257 + (mlx->player.wall_texture_offset * 2);
		texture_y = 210 + scaled_starting_point;
	}
	if (mlx->player.compass == 3) // South/Down
	{
		texture_x = 257 + (mlx->player.wall_texture_offset * 2);
		texture_y = 274 + scaled_starting_point;
	}
	if (mlx->player.compass == 4) // West/Left
	{
		texture_x = 1 + (mlx->player.wall_texture_offset * 2);
		texture_y = 274 + scaled_starting_point;
	}
	texture_pos = &mlx->texture.texture[texture_y][texture_x];
	color_x = 1;
	color_y = 4;
	while (color_y < 210)
	{
		if (mlx->texture.texture[color_y][color_x] == texture_pos[0])
		{
			if  (mlx->texture.texture[color_y][color_x + 1] == texture_pos[1])
			{
				color_x += 6;
				rgb = 0;
				while (rgb < 3)
				{
					/* Split the hex color to 2 characters and send them one by one to get the red, green, blue integer values. */
					
					if (rgb == 0)
						red = convert_hex_color_to_int(&mlx->texture.texture[color_y][color_x]);
					if (rgb == 1)
						green = convert_hex_color_to_int(&mlx->texture.texture[color_y][color_x]);
					if (rgb == 2)
						blue = convert_hex_color_to_int(&mlx->texture.texture[color_y][color_x]);
					rgb++;
					color_x += 2;
				}
				
				/* Bitshift the rgb colors to a single integer */
				
				mlx->texture.color = (alpha << 24) | (red << 16) | (green << 8) | blue;
				return (mlx->texture.color);
			}
		}
		color_y++;
	}
	return (-1);
}

double	scale_texture(int y, double oldmin, double oldmax)
{
	double	newmin;
	double	newmax;
	double	temp;
	double	result;

	newmin = 0;
	newmax = 64;
	temp = (newmax - newmin) * (y - oldmin);
	result = (temp / (oldmax - oldmin)) + newmin;
	return (result);
}

void	draw_pixel(t_mlx *mlx)
{
	char	*pixel;
	
	if ((mlx->draw.x1 >= 0 && mlx->draw.x1 <= mlx->img[1].width) && \
		(mlx->draw.y1 >= 0 && mlx->draw.y1 <= mlx->img[1].height))
	{
		pixel = mlx->img[1].img_addr + (((int)mlx->draw.y1 * mlx->img[1].size_line) + \
								((int)mlx->draw.x1 * (mlx->img[1].bits_per_pixel / 8)));
		*(int *)pixel = mlx->draw.color;
	}
}

void	render_column(int ray_nbr, t_mlx *mlx)
{
	int		projected_slice_height;
	double	temp;
	char	*texture;
	int		y_starting_point;
	int		y_end_point;
	double	texture_y;
	double	texture_y_offset;
	double	texture_y_increment;
	//int		index;

	mlx->draw.x1 = ray_nbr;
	mlx->draw.x2 = ray_nbr;
	mlx->draw.y1 = 0;
	mlx->draw.y2 = PROJECTION_PLANE_HEIGHT;
	
	/* Calculate the wall columns height that needs to be drawn */

	projected_slice_height = (double)SQUARE_SIZE / mlx->player.closest_coll_dist * mlx->player.dist_to_proj_plane;
	//projected_slice_height = ft_roundup(temp);
	
	texture_y_increment = (double)SQUARE_SIZE / (double)projected_slice_height;
	texture_y_offset = 0;

	if (projected_slice_height > PROJECTION_PLANE_HEIGHT)
	{
		texture_y_offset = (projected_slice_height - PROJECTION_PLANE_HEIGHT) / 2.0;
		projected_slice_height = PROJECTION_PLANE_HEIGHT;
	}
	
	y_starting_point = mlx->player.proj_plane_center_y - (projected_slice_height / 2); // Where to start drawing the column
	y_end_point = y_starting_point + projected_slice_height; // Where to end drawing the column
	
	/* Draw the sky */

	if (projected_slice_height < PROJECTION_PLANE_HEIGHT)
	{
		
		mlx->draw.y2 = y_starting_point;
		mlx->draw.color = LIGHT_BLUE;
		while (mlx->draw.y1 < mlx->draw.y2)
		{
			draw_pixel(mlx);
			mlx->draw.y1++;
		}
		mlx->draw.y2 = y_end_point;
	}

	texture_y = texture_y_offset * texture_y_increment;

	/* Draw the wall column */
	
	while (mlx->draw.y1 < mlx->draw.y2)
	{
		mlx->draw.color = choose_texture((int)texture_y, mlx);
		if (mlx->draw.color == -1) // Don't draw if we couldn't find a correct color
			exit (1);
		draw_pixel(mlx);
		texture_y += texture_y_increment;
		mlx->draw.y1++;
	}

	/* Draw the floor */

	if (y_end_point < PROJECTION_PLANE_HEIGHT)
	{
		mlx->draw.y2 = PROJECTION_PLANE_HEIGHT;
		mlx->draw.color = LIGHT_GREY;
		while (mlx->draw.y1 < mlx->draw.y2)
		{
			draw_pixel(mlx);
			mlx->draw.y1++;
		}
	}
}

void	fix_circle_angle(double *angle)
{
	if (*angle > 360.0)
		*angle -= 360.0;
	else if (*angle < 0.0)
		*angle += 360.0;
}

void	cast_rays(t_mlx *mlx)
{
	int		index;
	int		ray_nbr;
	double	hor_coll_dist;
	double	ver_coll_dist;
	double	fish_eye_fix_beta;

	mlx->player.ray_angle = mlx->player.pos_angle + (FOV / 2);
	fix_circle_angle(&mlx->player.ray_angle);
	ray_nbr = 0;
	while (ray_nbr < 320)
	{
		

		/* Calculate the closest collision point to a horizontal wall */
		
		hor_coll_dist = 100000;
		index = 0;
		
		if (mlx->player.ray_angle > 0 && mlx->player.ray_angle < 180) // Facing up
		{
			mlx->player.ray_y = (((int)mlx->player.pos_y >> 6) << 6) - 1;
			mlx->player.ray_x = mlx->player.pos_x + (mlx->player.pos_y - mlx->player.ray_y) / tan(ft_deg_to_rad(mlx->player.ray_angle));
			mlx->player.offset_y = -SQUARE_SIZE;
			mlx->player.offset_x = -mlx->player.offset_y / tan(ft_deg_to_rad(mlx->player.ray_angle));
		}
		else  if (mlx->player.ray_angle > 180 && mlx->player.ray_angle < 360) // Facing down
		{
			mlx->player.ray_y = (((int)mlx->player.pos_y >> 6) << 6) + SQUARE_SIZE;
			mlx->player.ray_x = mlx->player.pos_x + (mlx->player.pos_y - mlx->player.ray_y) / tan(ft_deg_to_rad(mlx->player.ray_angle));
			mlx->player.offset_y = SQUARE_SIZE;
			mlx->player.offset_x = -mlx->player.offset_y / tan(ft_deg_to_rad(mlx->player.ray_angle));
		}
		else
		{
			mlx->player.ray_x = mlx->player.pos_x;
			mlx->player.ray_y = mlx->player.pos_y;
			index = mlx->map.height;
		}
		
		while (index < mlx->map.height)
		{
			mlx->player.map_x = ((int)mlx->player.ray_x) >> 6;
			mlx->player.map_y = ((int)mlx->player.ray_y) >> 6;
			if (mlx->player.map_x >= 0 && mlx->player.map_x < mlx->map.width && \
				mlx->player.map_y >= 0 && mlx->player.map_y < mlx->map.height && \
				mlx->map.matrix[mlx->player.map_y][mlx->player.map_x] != 0)
			{
				mlx->player.hor_coll_point_x = mlx->player.ray_x;
				mlx->player.hor_coll_point_y = mlx->player.ray_y;
				hor_coll_dist = ray_collision_distance(&mlx->player, mlx->player.hor_coll_point_x, mlx->player.hor_coll_point_y); // Using square root to calculate
				//hor_coll_dist = ray_collision_distance_angles(mlx); // Using angles to calculate
				index = mlx->map.height;
			}
			else
			{
				mlx->player.ray_x += mlx->player.offset_x;
				mlx->player.ray_y += mlx->player.offset_y;
				index++;
			}
		}
		
		/* Calculate the closest collision point to a vertical wall */

		ver_coll_dist = 100000;
		index = 0;
		
		if (mlx->player.ray_angle > 90 && mlx->player.ray_angle < 270) // Facing left
		{
			mlx->player.ray_x = (((int)mlx->player.pos_x >> 6) << 6) - 1;
			mlx->player.ray_y = mlx->player.pos_y + (mlx->player.pos_x - mlx->player.ray_x) * tan(ft_deg_to_rad(mlx->player.ray_angle));
			mlx->player.offset_x = -SQUARE_SIZE;
			mlx->player.offset_y = -mlx->player.offset_x * tan(ft_deg_to_rad(mlx->player.ray_angle));
			index = 0;
		}
		else if ((mlx->player.ray_angle > 270 && mlx->player.ray_angle <= 360) || \
				(mlx->player.ray_angle >= 0 && mlx->player.ray_angle < 90))  // Facing right
		{
			mlx->player.ray_x = (((int)mlx->player.pos_x >> 6) << 6) + SQUARE_SIZE;
			mlx->player.ray_y = mlx->player.pos_y + (mlx->player.pos_x - mlx->player.ray_x) * tan(ft_deg_to_rad(mlx->player.ray_angle));
			mlx->player.offset_x = SQUARE_SIZE;
			mlx->player.offset_y = -mlx->player.offset_x * tan(ft_deg_to_rad(mlx->player.ray_angle));
			index = 0;
		}
		else
		{
			mlx->player.ray_x = mlx->player.pos_x;
			mlx->player.ray_y = mlx->player.pos_y;
			index = mlx->map.width;
		}
		while (index < mlx->map.width)
		{
			mlx->player.map_x = ((int)mlx->player.ray_x) >> 6;
			mlx->player.map_y = ((int)mlx->player.ray_y) >> 6;
			if (mlx->player.map_x >= 0 && mlx->player.map_x < mlx->map.width && \
				mlx->player.map_y >= 0 && mlx->player.map_y < mlx->map.height && \
				mlx->map.matrix[mlx->player.map_y][mlx->player.map_x] != 0)
			{
				mlx->player.ver_coll_point_x = mlx->player.ray_x;
				mlx->player.ver_coll_point_y = mlx->player.ray_y;
				ver_coll_dist = ray_collision_distance(&mlx->player, mlx->player.ver_coll_point_x, mlx->player.ver_coll_point_y); // Using square root to calculate
				//ver_coll_dist = ray_collision_distance_angles(mlx); // Using angles to calculate
				index = mlx->map.width;
			}
			else
			{
				mlx->player.ray_x += mlx->player.offset_x;
				mlx->player.ray_y += mlx->player.offset_y;
				index++;
			}
		}

		/* Saving the closest collision point values according to which of horizontal and vertical was closer */

		if (ver_coll_dist < hor_coll_dist)
		{
			mlx->draw.color = WHITE; // Choosing ray color - when ray hits a vertical wall first - for drawing the top down map
			mlx->player.closest_coll_dist = ver_coll_dist;
			mlx->player.ray_x = mlx->player.ver_coll_point_x;
			mlx->player.ray_y = mlx->player.ver_coll_point_y;
			mlx->player.wall_texture_offset = (int)mlx->player.ver_coll_point_y % SQUARE_SIZE; // Calculate which slice of the wall texture to draw
			if (mlx->player.ray_angle > 90 && mlx->player.ray_angle < 270) // Save which direction the ray is looking at. 2 = East/Right, 4 = West/Left
				mlx->player.compass = 4;
			else
				mlx->player.compass = 2;
		}
		else
		{
			mlx->draw.color = RED;	// Choosing ray color - when ray hits a horizontal wall first - for drawing the top down map
			mlx->player.closest_coll_dist = hor_coll_dist;
			mlx->player.ray_x = mlx->player.hor_coll_point_x;
			mlx->player.ray_y = mlx->player.hor_coll_point_y;
			mlx->player.wall_texture_offset = (int)mlx->player.hor_coll_point_x % SQUARE_SIZE; // Calculate which slice of the wall texture to draw
			if (mlx->player.ray_angle > 0 && mlx->player.ray_angle < 180) // Save which direction the ray is looking at. 1 = North/Up, 3 = South/Down
				mlx->player.compass = 1;
			else
				mlx->player.compass = 3;
		}

		/* Draw the top down map */
		
		mlx->draw.x1 = mlx->player.pos_x;
		mlx->draw.y1 = mlx->player.pos_y;
		mlx->draw.x2 = mlx->player.ray_x;
		mlx->draw.y2 = mlx->player.ray_y;
		draw_line(&mlx->draw, &mlx->img[0]);

		/* Fix the fisheye effect (distortion) */
		fish_eye_fix_beta = mlx->player.pos_angle - mlx->player.ray_angle;
		mlx->player.closest_coll_dist = mlx->player.closest_coll_dist * cos(ft_deg_to_rad(fish_eye_fix_beta));

		/* Render column if we are not on top of a wall */
		if (mlx->player.closest_coll_dist > 0)
			render_column(ray_nbr, mlx);
			
		ray_nbr += 1;
		mlx->player.ray_angle -= mlx->player.degrees_per_ray;
		fix_circle_angle(&mlx->player.ray_angle);
	}
}
