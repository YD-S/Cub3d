/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_map_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 19:57:05 by delvira-          #+#    #+#             */
/*   Updated: 2023/08/24 20:03:39 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	ft_sign(int x0, int x1)
{
	if (x0 < x1)
		return (1);
	else
		return (-1);
}

void	draw_lines(t_point point0, t_point point1, mlx_image_t *img)
{
	t_ints	i;

	i.dx = fabsf(point1.xcoord - point0.xcoord);
	i.dy = -fabsf(point1.ycoord - point0.ycoord);
	i.err = i.dx + i.dy;
	while (1)
	{
		ft_put_pixel(img, point0.xcoord, point0.ycoord, 0x000000FF);
		if (fabsf(point0.xcoord - point1.xcoord) < 1
			&& fabsf(point0.ycoord - point1.ycoord) < 1)
			break ;
		i.e2 = 2 * i.err;
		if (i.e2 >= i.dy)
		{
			i.err += i.dy;
			point0.xcoord += ft_sign(point0.xcoord, point1.xcoord);
		}
		if (i.e2 <= i.dx)
		{
			i.err += i.dx;
			point0.ycoord += ft_sign(point0.ycoord, point1.ycoord);
		}
	}
}

void	free_str_array(char **array)
{
	int	x;

	x = 0;
	while (array[x])
	{
		free(array[x]);
		x++;
	}
	free(array);
}

void	paint_image_black(t_mlx_data mlx_data)
{
	int		x;
	int		i;

	x = 0;
	i = 0;
	while (x < SCREEN_WIDTH)
	{
		i = 0;
		while (i < SCREEN_HEIGH)
		{
			if (i > SCREEN_HEIGH / 2)
				ft_put_pixel(mlx_data.img, x, i,
					get_rgba(mlx_data.map_data.f_color[0],
						mlx_data.map_data.f_color[1],
						mlx_data.map_data.f_color[2], 255));
			else
				ft_put_pixel(mlx_data.img, x, i,
					get_rgba(mlx_data.map_data.c_color[0],
						mlx_data.map_data.c_color[1],
						mlx_data.map_data.c_color[2], 255));
			i++;
		}
		x++;
	}
}
