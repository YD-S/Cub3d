/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysingh <ysingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 19:57:53 by delvira-          #+#    #+#             */
/*   Updated: 2023/08/24 21:48:56 by ysingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_t_map(t_map **map)
{
	int	x;

	x = 0;
	while (map[x])
	{
		free(map[x]);
		x++;
	}
	free(map);
	exit_error("Error\nMap must have one player\n");
}

void	do_cpy(t_map **map, t_map **cpy_map, int x, int y)
{
	cpy_map[x][y].value = map[x][y].value;
	cpy_map[x][y].point.xcoord = map[x][y].point.xcoord;
	cpy_map[x][y].point.ycoord = map[x][y].point.ycoord;
	cpy_map[x][y].point.type = map[x][y].point.type;
}
