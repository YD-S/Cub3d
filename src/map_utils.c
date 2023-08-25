/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 19:56:45 by delvira-          #+#    #+#             */
/*   Updated: 2023/08/24 19:59:56 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	**get_map(char *map_name, t_map_data map_data)
{
	t_map	**map;

	map = get_map_malloc(map_data);
	map = fill_map_spaces(map, map_data);
	map = fill_map_values(map, map_name);
	return (map);
}

int	*init_f_color(t_map_data map_data)
{
	int		*f_color;
	char	**floor_split;

	f_color = ft_calloc(3, sizeof(int));
	floor_split = ft_split(map_data.f, ',');
	f_color[0] = ft_atoi(floor_split[0]);
	f_color[1] = ft_atoi(floor_split[1]);
	f_color[2] = ft_atoi(floor_split[2]);
	free_str_array(floor_split);
	return (f_color);
}

int	*init_c_color(t_map_data map_data)
{
	int		*c_color;
	char	**ceil_split;

	c_color = ft_calloc(3, sizeof(int));
	ceil_split = ft_split(map_data.c, ',');
	c_color[0] = ft_atoi(ceil_split[0]);
	c_color[1] = ft_atoi(ceil_split[1]);
	c_color[2] = ft_atoi(ceil_split[2]);
	free_str_array(ceil_split);
	return (c_color);
}

void	init_all(int *x, int *i, char **line, int fd)
{
	*line = get_next_line(fd);
	*x = 0;
	*i = 0;
}
