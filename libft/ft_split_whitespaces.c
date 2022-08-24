/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 01:50:14 by raho              #+#    #+#             */
/*   Updated: 2022/04/13 05:05:24 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char *str)
{
	int	index;
	int	counter;

	index = 0;
	counter = 0;
	while (str[index] != '\0')
	{
		while (str[index] == ' ' || str[index] == '\t' || str[index] == '\n')
			index++;
		if (str[index] != '\0')
		{
			counter++;
			while (str[index] != '\0' && str[index] != ' ' && str[index] != \
					'\t' && str[index] != '\n')
				index++;
		}
	}
	return (counter);
}

static int	count_characters(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
		i++;
	return (i);
}

static void	copy_next_word(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0' && src[i] != ' ' && src[i] != '\t' && src[i] != '\n')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

char	**ft_split_whitespaces(char *str)
{
	int		index;
	int		word_count;
	int		character_count;
	char	**new;

	word_count = count_words(str);
	new = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (new == NULL)
		return (0);
	index = 0;
	character_count = 0;
	while (index < word_count)
	{
		while (*str == ' ' || *str == '\t' || *str == '\n')
			str++;
		character_count = count_characters(str);
		new[index] = (char *)malloc(sizeof(char) * (character_count + 1));
		if (new[index] == NULL)
			return (0);
		copy_next_word(new[index], str);
		str = str + character_count;
		index++;
	}
	new[index] = 0;
	return (new);
}
