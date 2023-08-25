/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 19:57:48 by delvira-          #+#    #+#             */
/*   Updated: 2023/08/24 20:04:11 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map_data	do_parse(char *line, t_map_data map_data, int i)
{
	if (line[i] == 'N' && line[i + 1] == 'O')
		return (do_no(line, map_data));
	else if (line[i] == 'S' && line[i + 1] == 'O')
		return (do_so(line, map_data));
	else if (line[i] == 'W' && line[i + 1] == 'E')
		return (do_we(line, map_data));
	else if (line[i] == 'E' && line[i + 1] == 'A')
		return (do_ea(line, map_data));
	else if (line[i] == 'F')
	{
		map_data.f = parse_f(line);
		return (map_data);
	}
	else if (line[i] == 'C')
	{
		map_data.c = parse_c(line);
		return (map_data);
	}
	else
		return (map_data);
}

t_map_data	parse_line(char *line, t_map_data map_data)
{
	int	i;

	i = 0;
	while (line[i])
	{
		return (do_parse(line, map_data, i));
		i++;
	}
	return (map_data);
}

t_map_data	map_data_init(void)
{
	t_map_data	map_data;

	map_data.no = NULL;
	map_data.so = NULL;
	map_data.we = NULL;
	map_data.ea = NULL;
	return (map_data);
}

t_map_data	read_map_utils(char *map)
{
	char		*line;
	int			fd;
	int			x;
	t_map_data	map_data;

	fd = open(map, O_RDONLY);
	line = get_next_line(fd);
	map_data = map_data_init();
	x = 0;
	while (line)
	{
		if (line[0] == '\n')
		{
		}
		else if (x < 6)
		{
			map_data = parse_line(line, map_data);
			x++;
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (map_data);
}

int	get_map_heigh(char *map)
{
	char	*line;
	int		i;
	int		fd;
	int		x;

	fd = open(map, O_RDONLY);
	line = get_next_line(fd);
	x = 0;
	i = 0;
	while (line)
	{
		if (line[0] == '\n')
		{
		}
		else if (x < 6)
		{
			x++;
		}
		else if (x >= 6)
			i++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (i);
}
