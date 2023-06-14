
#include "cub3d.h"

char	*parse_NO(char *line)
{
	int		i;
	int		x;
	char	*str;

	i = 0;
	x = 0;
	str = ft_calloc(ft_strlen(line) + 2, sizeof(char));
	while (line[i] == ' ' || line[i] == '\n')
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O')
		i += 2;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\n')
			i++;
		else
		{
			str[x] = line[i];
			i++;
			x++;
		}
	}
	return (str);
}

char	*parse_WE(char *line)
{
	int		i;
	int		x;
	char	*str;

	i = 0;
	x = 0;
	str = ft_calloc(ft_strlen(line) + 2, sizeof(char));
	while (line[i] == ' ' || line[i] == '\n')
		i++;
	if (line[i] == 'W' && line[i + 1] == 'E')
		i += 2;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\n')
			i++;
		else
		{
			str[x] = line[i];
			i++;
			x++;
		}
	}
	return (str);
}

char	*parse_SO(char *line)
{
	int		i;
	int		x;
	char	*str;

	i = 0;
	x = 0;
	str = ft_calloc(ft_strlen(line) + 2, sizeof(char));
	while (line[i] == ' ' || line[i] == '\n')
		i++;
	if (line[i] == 'S' && line[i + 1] == 'O')
		i += 2;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\n')
			i++;
		else
		{
			str[x] = line[i];
			i++;
			x++;
		}
	}
	return (str);
}

char	*parse_EA(char *line)
{
	int		i;
	int		x;
	char	*str;

	i = 0;
	x = 0;
	str = ft_calloc(ft_strlen(line) + 2, sizeof(char));
	while (line[i] == ' ' || line[i] == '\n')
		i++;
	if (line[i] == 'E' && line[i + 1] == 'A')
		i += 2;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\n')
			i++;
		else
		{
			str[x] = line[i];
			i++;
			x++;
		}
	}
	return (str);
}

char	*parse_F(char *line)
{
	int		i;
	int		x;
	char	*str;

	i = 0;
	x = 0;
	str = ft_calloc(ft_strlen(line) + 2, sizeof(char));
	while (line[i] == ' ' || line[i] == '\n')
		i++;
	if (line[i] == 'F')
		i += 1;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\n')
			i++;
		else
		{
			str[x] = line[i];
			i++;
			x++;
		}
	}
	return (str);
}

char	*parse_C(char *line)
{
	int		i;
	int		x;
	char	*str;

	i = 0;
	x = 0;
	str = ft_calloc(ft_strlen(line) + 2, sizeof(char));
	while (line[i] == ' ' || line[i] == '\n')
		i++;
	if (line[i] == 'C')
		i += 1;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\n')
			i++;
		else
		{
			str[x] = line[i];
			i++;
			x++;
		}
	}
	return (str);
}

t_map_data	parse_line(char *line, t_map_data map_data)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'N' && line[i + 1] == 'O')
		{
			map_data.NO = parse_NO(line);
			map_data.count.NO++;
			map_data.count.total++;
			return (map_data);
		}
		else if (line[i] == 'S' && line[i + 1] == 'O')
		{
			map_data.SO = parse_SO(line);
			map_data.count.SO++;
			map_data.count.total++;
			return (map_data);
		}
		else if (line[i] == 'W' && line[i + 1] == 'E')
		{
			map_data.WE = parse_WE(line);
			map_data.count.WE++;
			map_data.count.total++;
			return (map_data);
		}
		else if (line[i] == 'E' && line[i + 1] == 'A')
		{
			map_data.EA = parse_EA(line);
			map_data.count.EA++;
			map_data.count.total++;
			return (map_data);
		}
		else if (line[i] == 'F')
		{
			map_data.F = parse_F(line);
			map_data.count.F++;
			map_data.count.total++;
			return (map_data);
		}
		else if (line[i] == 'C')
		{
			map_data.C = parse_C(line);
			map_data.count.C++;
			map_data.count.total++;
			return (map_data);
		}
		i++;
	}
	return (map_data);
}

void count_init(t_data_count *count)
{
	count->total = 0;
	count->NO = 0;
	count->SO = 0;
	count->WE = 0;
	count->EA = 0;
	count->F = 0;
	count->C = 0;
}

t_map_data	map_data_init(void)
{
	t_map_data	map_data;

	count_init(&map_data.count);
	map_data.NO = NULL;
	map_data.SO = NULL;
	map_data.WE = NULL;
	map_data.EA = NULL;
	return (map_data);
}

int get_count(t_data_count count)
{
	return ((count.total != 6 || count.NO != 1 || count.SO != 1 || count.WE != 1 || count.EA != 1 || count.F != 1 || count.C != 1));
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
	if(get_count(map_data.count))
	{
		printf("Error\n");
		exit(0);
	}
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

int	get_map_width(char *map)
{
	char	*line;
	int		i;
	int		fd;
	int		x;
	int		width;

	fd = open(map, O_RDONLY);
	line = get_next_line(fd);
	x = 0;
	i = 0;
	width = 0;
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
		{
			i = ft_strlen(line);
			if (i > width)
				width = i;
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (width - 1);
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
	char	*line;
	int		i;
	int		fd;
	int		x;
	int		j;

	fd = open(map_name, O_RDONLY);
	line = get_next_line(fd);
	x = 0;
	i = 0;
	j = 0;
	while (line)
	{
		if (line[0] == '\n')
		{
		}
		else if (x < 6)
			x++;
		else if (x >= 6)
		{
			i = 0;
			while (line[i] != '\n' && line[i] != '\0')
			{
				map[j][i].value = line[i];
				i++;
			}
			j++;
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (map);
}

t_map	**get_map(char *map_name, t_map_data map_data)
{
	t_map	**map;

	map = get_map_malloc(map_data);
	map = fill_map_spaces(map, map_data);
	map = fill_map_values(map, map_name);
	return (map);
}

t_map_data	parse_map(char *map)
{
	t_map_data	map_data;

	map_data = read_map_utils(map);
	map_data.heigh = get_map_heigh(map);
	map_data.width = get_map_width(map);
	map_data.map = get_map(map, map_data);
	return (map_data);
}
