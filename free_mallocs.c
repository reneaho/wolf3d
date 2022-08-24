/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mallocs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 19:01:18 by raho              #+#    #+#             */
/*   Updated: 2022/08/14 21:48:43 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void    free_matrix(int height, t_map *map)
{
    int index;

    index = 0;
    while (index < height)
    {
        free(map->matrix[index]);
        index++;
    }
    free(map->matrix);
}
