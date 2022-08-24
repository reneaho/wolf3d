/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 20:05:07 by raho              #+#    #+#             */
/*   Updated: 2022/07/25 13:16:51 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	char	*temp;

	if (s1 && s2)
	{
		new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + \
											ft_strlen(s2) + 1));
		if (!new)
			return (NULL);
		temp = new;
		while (*s1 != '\0')
			*new++ = *s1++;
		while (*s2 != '\0')
			*new++ = *s2++;
		*new = '\0';
		return (temp);
	}
	return (NULL);
}
