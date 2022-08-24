/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaling_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 17:44:02 by raho              #+#    #+#             */
/*   Updated: 2022/08/21 19:58:16 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double	scale_value_x(int x, double newmin, double newmax)
{
	double	oldmin;
	double	oldmax;
	double	temp;
	double	result;

	oldmin = 0;
	oldmax = WINDOW_SIZE_WIDTH;
	temp = (newmax - newmin) * (x - oldmin);
	result = (temp / (oldmax - oldmin)) + newmin;
	return (result);
}

double	scale_value_y(int y, double newmin, double newmax)
{
	double	oldmin;
	double	oldmax;
	double	temp;
	double	result;

	oldmin = 0;
	oldmax = WINDOW_SIZE_HEIGHT;
	temp = (newmax - newmin) * (y - oldmin);
	result = (temp / (oldmax - oldmin)) + newmin;
	return (result);
}
