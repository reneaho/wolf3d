/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_to_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 03:33:42 by raho              #+#    #+#             */
/*   Updated: 2022/12/17 03:36:32 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Converts a 2 character long hex code to integer form */
int	ft_hex_to_int(char *hexcolor)
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