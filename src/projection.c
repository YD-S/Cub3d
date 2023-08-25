/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 19:49:14 by delvira-          #+#    #+#             */
/*   Updated: 2023/08/24 20:04:25 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	reversecolor(unsigned int coloraux)
{
	int	red;
	int	green;
	int	blue;
	int	alpha;

	red = coloraux >> 24;
	green = coloraux << 8 >> 24;
	blue = coloraux << 16 >> 24;
	alpha = coloraux << 24 >> 24;
	return (get_rgba(alpha, blue, green, red));
}

uint32_t	gettexcolor(char tex, int x, int y, t_mlx_data mlx_data)
{
	uint32_t	color;

	color = 0;
	if (x + y * mlx_data.map_data.texture.no->width
		< mlx_data.map_data.texture.no->width
		* mlx_data.map_data.texture.no->height)
	{
		if (tex == 'N')
			color = ((unsigned int *)
					mlx_data.map_data.texture.no->pixels)[x + y
				* mlx_data.map_data.texture.no->width];
		else if (tex == 'S')
			color = ((unsigned int *)
					mlx_data.map_data.texture.so->pixels)[x + y
				* mlx_data.map_data.texture.so->width];
		else if (tex == 'W')
			color = ((unsigned int *)mlx_data.map_data.texture.we->pixels)[x + y
				* mlx_data.map_data.texture.we->width];
		else if (tex == 'E')
			color = ((unsigned int *)mlx_data.map_data.texture.ea->pixels)[x + y
				* mlx_data.map_data.texture.ea->width];
	}
	return (reversecolor(color));
}

void	paint_square_td(t_mlx_data mlx_data, int height, int x_start, int color)
{
	int		y;
	char	tex;
	int		xtex;
	float	step;

	y = 0;
	xtex = 0;
	step = 0;
	(void)color;
	tex = ft_texture(&mlx_data, x_start, (SCREEN_HEIGH / 2) - (height / 2) + y);
	xtex = getxtex(tex, x_start, mlx_data);
	step = getstep(height, mlx_data, tex);
	while (y < height && (SCREEN_HEIGH / 2) - (height / 2) + y < SCREEN_HEIGH)
	{
		ft_put_pixel(mlx_data.img, x_start, (SCREEN_HEIGH / 2)
			- (height / 2) + y, gettexcolor(tex, xtex, y * step, mlx_data));
		y++;
	}
}

void	projection(t_mlx_data mlx_data)
{
	int		i;
	int		color;
	int		x_start;
	float	ray_height;

	i = 0;
	x_start = 0;
	while (i < mlx_data.proj_data.n_rays)
	{
		ray_height = SCREEN_HEIGH / (mlx_data.proj_data.ray_array[i].distance)
			* WALL_HEIGHT_SCALE * 0.3;
		mlx_data.proj_data.ray_array[i].ray_heigh = ray_height;
		color = 255 - 255 * (mlx_data.proj_data.ray_array[i].distance / 1000);
		paint_square_td(mlx_data, ray_height, x_start, color);
		i++;
		x_start += 1;
	}
}
