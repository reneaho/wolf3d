/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rad_to_deg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 19:49:56 by raho              #+#    #+#             */
/*   Updated: 2022/12/17 04:13:20 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_rad_to_deg(double radians)
{
	double	degrees;

	degrees = radians * 180.0 / (double)M_PI;
	return (degrees);
}
