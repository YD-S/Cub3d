/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 19:56:35 by delvira-          #+#    #+#             */
/*   Updated: 2023/08/24 19:59:54 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_map_width(char *map)
{
	char	*line;
	int		i;
	int		fd;
	int		x;
	int		width;

	fd = open(map, O_RDONLY);
	init_all(&x, &width, &line, fd);
	width = 0;
	while (line)
	{
		if (line[0] == '\n')
			;
		else if (x < 6)
			x++;
		else if (x >= 6)
		{
			i = ft_strlen(line);
			if (i > width)
				width = i;
		}
		free(line);
		line = get_next_line(fd);
	}
	return (free(line), width - 1);
}

t_map	**get_map_malloc(t_map_data map_data)
{
	t_map	**map;
	int		x;

	x = 0;
	map = ft_calloc(map_data.heigh + 1, sizeof(t_map *));
	while (x < map_data.heigh)
	{
		map[x] = ft_calloc(map_data.width + 1, sizeof(t_map));
		x++;
	}
	return (map);
}

t_map	**fill_map_spaces(t_map **map, t_map_data map_data)
{
	int	x;
	int	i;

	x = 0;
	i = 0;
	while (x < map_data.heigh)
	{
		i = 0;
		while (i < map_data.width)
		{
			map[x][i].value = ' ';
			map[x][i].point.xcoord = i * PIXEL_SIZE;
			map[x][i].point.ycoord = x * PIXEL_SIZE;
			i++;
		}
		x++;
	}
	return (map);
}

t_map	**fill_map_values(t_map **map, char *map_name)
{
	char		*line;
	t_counts	i;

	i.fd = open(map_name, O_RDONLY);
	init_all(&i.x, &i.j, &line, i.fd);
	while (line)
	{
		if (line[0] == '\n')
			;
		else if (i.x < 6)
			i.x++;
		else if (i.x >= 6)
		{
			i.i = 0;
			while (line[i.i] != '\n' && line[i.i] != '\0')
			{
				map[i.j][i.i].value = line[i.i];
				i.i++;
			}
			i.j++;
		}
		free(line);
		line = get_next_line(i.fd);
	}
	return (free(line), map);
}

t_map_data	parse_map(char *map)
{
	t_map_data	map_data;

	map_data = read_map_utils(map);
	map_data.heigh = get_map_heigh(map);
	map_data.width = get_map_width(map);
	map_data.map = get_map(map, map_data);
	map_data.f_color = init_f_color(map_data);
	map_data.c_color = init_c_color(map_data);
	return (map_data);
}
