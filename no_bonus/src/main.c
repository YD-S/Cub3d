/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 19:56:23 by delvira-          #+#    #+#             */
/*   Updated: 2023/08/24 19:59:28 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	leaks(void)
{
	system("leaks -q cub3d");
}

void	free_map(t_map_data map_data)
{
	int	x;

	free(map_data.c);
	free(map_data.f);
	free(map_data.so);
	free(map_data.no);
	free(map_data.ea);
	free(map_data.we);
	free(map_data.f_color);
	free(map_data.c_color);
	x = 0;
	while (map_data.map[x])
	{
		free(map_data.map[x]);
		x++;
	}
	free(map_data.map);
}

void	print_map(t_map_data map_data)
{
	int	x;
	int	i;

	printf("NO: %s\n", map_data.no);
	printf("SO: %s\n", map_data.so);
	printf("WE: %s\n", map_data.we);
	printf("EA: %s\n", map_data.ea);
	printf("F: %s\n", map_data.f);
	printf("C: %s\n", map_data.c);
	printf("heigh: %i\n", map_data.heigh);
	printf("width: %i\n", map_data.width);
	x = 0;
	i = 0;
	while (x < map_data.heigh)
	{
		i = 0;
		while (i < map_data.width)
		{
			printf("%c", map_data.map[x][i].value);
			i++;
		}
		x++;
		printf("\n");
	}
}

int	verify_path(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		ft_printf("File error\n");
		exit(0);
	}
	close(fd);
	return (0);
}

int	main(int nargs, char **args)
{
	t_mlx_data	mlx_data;

	atexit(leaks);
	verify_path(args[1]);
	if (nargs != 2)
		exit(0);
	mlx_data = init_mlx_data(args[1]);
	verify_path(mlx_data.map_data.no);
	verify_path(mlx_data.map_data.so);
	verify_path(mlx_data.map_data.we);
	verify_path(mlx_data.map_data.ea);
	open_map(mlx_data);
	free_map(mlx_data.map_data);
}
