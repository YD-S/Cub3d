/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 19:57:10 by delvira-          #+#    #+#             */
/*   Updated: 2023/08/25 17:41:07 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int			x_coord;
	int			y_coord;
	t_counts	i;

	i.x = 0;
	x_coord = 0;
	while (i.x < mlx_data.map_data.heigh)
	{
		i.i = 0;
		y_coord = 0;
		while (i.i < mlx_data.map_data.width)
		{
			if (mlx_data.map_data.map[i.x][i.i].value == '1')
				paint_square(x_coord, y_coord, mlx_data, get_rgba(0, 100, 255,
						205));
			else if (mlx_data.map_data.map[i.x][i.i].value == '0'
					|| condition1(mlx_data, i.x, i.i))
				paint_square(x_coord, y_coord, mlx_data, get_rgba(0, 255, 155,
						205));
			i.i++;
			y_coord += PIXEL_SIZE;
		}
		i.x++;
		x_coord += PIXEL_SIZE;
	}
}

void	put_player(t_mlx_data mlx_data)
{
	int		x;
	int		y;
	int		radius;

	radius = PIXEL_SIZE / 2 -1;
	x = 0;
	while (x <= PIXEL_SIZE)
	{
		y = 0;
		while (y <= PIXEL_SIZE)
		{
			if (condition6(mlx_data, radius, x, y))
			{
				ft_put_pixel(mlx_data.img, mlx_data.player.position.xcoord
					- PIXEL_SIZE / 2 + x, mlx_data.player.position.ycoord
					- PIXEL_SIZE / 2 + y, get_rgba(255, 0, 0, 255));
			}
			y++;
		}
		x++;
	}
	paint_circle(x, y, radius, mlx_data);
}

t_projection_data	init_proj_data(void)
{
	t_projection_data	proj_data;

	proj_data.n_rays = 30 / (RAY_DIV / SCREEN_WIDTH);
	proj_data.ray_array = ft_calloc(proj_data.n_rays + 1, sizeof(t_ray));
	return (proj_data);
}

void	open_map(t_mlx_data mlx_data)
{
	mlx_data.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGH, "cub3d", false);
	mlx_data.img = mlx_new_image(mlx_data.mlx, SCREEN_WIDTH, SCREEN_HEIGH);
	mlx_image_to_window(mlx_data.mlx, mlx_data.img, 0, 0);
	ft_get_texture(&mlx_data);
	paint_image_black(mlx_data);
	mlx_data.player = init_player(mlx_data);
	mlx_data.proj_data = init_proj_data();
	mlx_data = put_ray(mlx_data);
	projection(mlx_data);
	mlx_key_hook(mlx_data.mlx, &hook, (void *)&mlx_data);
	mlx_loop_hook(mlx_data.mlx, (void *)&repaint_map, (void *)&mlx_data);
	mlx_loop(mlx_data.mlx);
	free(mlx_data.proj_data.ray_array);
	mlx_terminate(mlx_data.mlx);
	mlx_delete_texture(mlx_data.map_data.texture.no);
	mlx_delete_texture(mlx_data.map_data.texture.so);
	mlx_delete_texture(mlx_data.map_data.texture.ea);
	mlx_delete_texture(mlx_data.map_data.texture.we);
}
