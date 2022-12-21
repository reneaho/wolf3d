/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deg_to_rad.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 19:52:31 by raho              #+#    #+#             */
/*   Updated: 2022/12/17 04:13:22 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_deg_to_rad(double degrees)
{
	double	radians;

	radians = (degrees * (double)M_PI) / 180.0;
	return (radians);
}
