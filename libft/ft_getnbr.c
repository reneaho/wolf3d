/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:38:18 by raho              #+#    #+#             */
/*   Updated: 2022/07/18 15:02:27 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Takes a string of numbers and returns them as an integer.
*/

int	ft_getnbr(char *str)
{
	int	index;
	int	result;

	index = 0;
	result = 0;
	if (str[index] == '-' || str[index] == '+')
		index++;
	while (str[index] >= 48 && str[index] <= 57)
	{
		result = result * 10 + (str[index] - 48);
		index++;
	}
	if (str[0] == '-')
		return (result * (-1));
	return (result);
}
