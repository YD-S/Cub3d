
#include "cub3d.h"

void	paint_square(int x_coord, int y_coord, t_mlx_data mlx_data,
		uint32_t color)
{
	int	x;
	int	i;

	x = 0;
	i = 0;
	while (x < PIXEL_SIZE)
	{
		i = 0;
		while (i < PIXEL_SIZE)
		{
			ft_put_pixel(mlx_data.img, y_coord + x, x_coord + i, color);
			i++;
		}
		x++;
	}
}

void	paint_map(t_mlx_data mlx_data)
{
	int	x_coord;
	int	y_coord;
	int	x;
	int	y;

	x = 0;
	x_coord = 0;
	y_coord = 0;
	while (x < mlx_data.map_data.heigh)
	{
		y = 0;
		y_coord = 0;
		while (y < mlx_data.map_data.width)
		{
			if (mlx_data.map_data.map[x][y].value == '1')
				paint_square(x_coord, y_coord, mlx_data, get_rgba(0, 100, 255,
						205));
			else if (mlx_data.map_data.map[x][y].value == '0'
					|| condition1(mlx_data, x, y))
				paint_square(x_coord, y_coord, mlx_data, get_rgba(0, 255, 155,
						205));
			y++;
			y_coord += PIXEL_SIZE;
		}
		x++;
		x_coord += PIXEL_SIZE;
	}
}


void	put_player(t_mlx_data mlx_data)
{
	int		x;
	int		y;
	float	a;
	int		radius;

	radius = PIXEL_SIZE / 2 - 10;
	x = 0;
	while (x <= PIXEL_SIZE)
	{
		y = 0;
		while (y <= PIXEL_SIZE)
		{
			if (pow(((mlx_data.player.position.xcoord - PIXEL_SIZE / 2 + x)
						- (mlx_data.player.position.xcoord)), 2)
				+ pow(((mlx_data.player.position.ycoord - PIXEL_SIZE / 2 + y)
						- (mlx_data.player.position.ycoord)), 2) <= pow(radius,
					2))
			{
				ft_put_pixel(mlx_data.img, mlx_data.player.position.xcoord
					- PIXEL_SIZE / 2 + x, mlx_data.player.position.ycoord
					- PIXEL_SIZE / 2 + y, get_rgba(255, 0, 0, 255));
			}
			y++;
		}
		x++;
	}
	a = 0;
	while (a <= M_PI * 2)
	{
		x = cos(a) * radius + mlx_data.player.position.xcoord;
		y = sin(a) * radius + mlx_data.player.position.ycoord;
		ft_put_pixel(mlx_data.img, x, y, get_rgba(0, 0, 0, 255));
		a += 0.01;
	}
}

t_projection_data	init_proj_data(void)
{
	t_projection_data	proj_data;

	proj_data.n_rays = 30 / RAY_DIV;
	proj_data.ray_array = ft_calloc(proj_data.n_rays + 1, sizeof(t_ray));
	return (proj_data);
}

void	open_map(t_mlx_data mlx_data)
{
	mlx_data.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGH, "cub3d", false);
	//mlx_set_cursor_mode(mlx_data.mlx, MLX_MOUSE_HIDDEN);
	mlx_data.img = mlx_new_image(mlx_data.mlx, SCREEN_WIDTH, SCREEN_HEIGH);
	mlx_image_to_window(mlx_data.mlx, mlx_data.img, 0, 0);
	ft_get_texture(&mlx_data);
	paint_image_black(mlx_data);
	//paint_map(mlx_data);
	// paint_horizontal_lines(mlx_data);
	// paint_vertical_lines(mlx_data);
	mlx_data.player = init_player(mlx_data);
	//put_player(mlx_data);
	mlx_data.proj_data = init_proj_data();
	mlx_data = put_ray(mlx_data);
	projection(mlx_data);
	mlx_key_hook(mlx_data.mlx, &hook, (void *)&mlx_data);
	//mlx_cursor_hook(mlx_data.mlx, &cursor_hook, (void *)&mlx_data);
	mlx_loop_hook(mlx_data.mlx, (void *)&repaint_map, (void *)&mlx_data);
	mlx_loop(mlx_data.mlx);
	free(mlx_data.proj_data.ray_array);
	mlx_terminate(mlx_data.mlx);
	mlx_delete_texture(mlx_data.map_data.texture.no);
	mlx_delete_texture(mlx_data.map_data.texture.so);
	mlx_delete_texture(mlx_data.map_data.texture.ea);
	mlx_delete_texture(mlx_data.map_data.texture.we);
}
