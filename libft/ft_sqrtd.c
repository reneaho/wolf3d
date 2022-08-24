/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrtd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 11:00:55 by raho              #+#    #+#             */
/*   Updated: 2022/08/23 10:40:48 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Returns the square root of the given value as double. */

double	ft_sqrtd(double nb)
{
	double	sqrt;
	double	temp;

	sqrt = nb / 2;	// -50
	temp = 0;
	while (sqrt != temp)
	{
		temp = sqrt;	// -100.5
		sqrt = ((nb / temp) + temp) / 2;
	}		//	-100 / 0.49621255 = 1
			//	1 + -100 = -100
			//	100 / 2 = -100.5

	return (sqrt);
}
