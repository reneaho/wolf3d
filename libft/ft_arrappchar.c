/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrappchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 02:41:55 by raho              #+#    #+#             */
/*   Updated: 2022/07/21 13:33:29 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Takes an array of strings, string to append and the nbr of strings already
** in the array. Duplicates the array of strings and appends the *str to the
** end of it. Frees the original array.
*/

char	**ft_arrappchar(char **arr, char *str, unsigned int n)
{
	unsigned int	index;
	char			**result;

	result = NULL;
	index = 0;
	result = (char **)malloc(sizeof(char *) * (n + 2));
	if (!result)
		return (NULL);
	if (index != n)
	{
		while (index != n)
		{
			result[index] = ft_strdup(arr[index]);
			free(arr[index]);
			index++;
		}
		free(arr);
	}
	result[index] = ft_strdup(str);
	result[index + 1] = NULL;
	return (result);
}
