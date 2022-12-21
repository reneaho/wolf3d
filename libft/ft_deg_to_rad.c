/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deg_to_rad.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 19:52:31 by raho              #+#    #+#             */
/*   Updated: 2022/12/21 15:12:11 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_deg_to_rad(float degrees)
{
	float	radians;

	radians = (degrees * (float)M_PI) / 180.0f;
	return (radians);
}
