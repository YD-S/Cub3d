
#include "cub3d.h"

void	leaks(void)
{
	system("leaks -q cub3d");
}

void	free_map(t_map_data map_data)
{
	int	x;

	free(map_data.C);
	free(map_data.F);
	free(map_data.SO);
	free(map_data.NO);
	free(map_data.EA);
	free(map_data.WE);
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

	printf("NO: %s\n", map_data.NO);
	printf("SO: %s\n", map_data.SO);
	printf("WE: %s\n", map_data.WE);
	printf("EA: %s\n", map_data.EA);
	printf("F: %s\n", map_data.F);
	printf("C: %s\n", map_data.C);
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

int verify_path(char *str)
{
	int fd;
	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		return (ft_printf("File error\n"),1);
	}
	close(fd);
	return (0);
}

int	main(int nargs, char **args)
{
	t_mlx_data	mlx_data;

	atexit(leaks);
	if (nargs != 2 || verify_path(args[1]))
		exit(0);
	mlx_data = init_mlx_data(args[1]);
	open_map(mlx_data);
	print_map(mlx_data.map_data);
	free_map(mlx_data.map_data);
}
