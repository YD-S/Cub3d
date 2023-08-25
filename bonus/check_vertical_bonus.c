/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_vertical.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 19:41:35 by delvira-          #+#    #+#             */
/*   Updated: 2023/08/24 20:00:59 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point	ver_1st_loop(t_mlx_data mlx_data, float x, float y, float angle)
{
	t_point	p1;

	while (1)
	{
		if (x < 0 || y < 0 || x > (mlx_data.map_data.width - 1)
			* PIXEL_SIZE || y > (mlx_data.map_data.heigh) * PIXEL_SIZE
			|| (int)(y / PIXEL_SIZE) - 1 > mlx_data.map_data.heigh
				|| (int)((x) / PIXEL_SIZE) > mlx_data.map_data.width)
		{
			x = 3500;
			y = 3300;
			break ;
		}
		else if ((int)((y) / PIXEL_SIZE) < mlx_data.map_data.heigh
				&& (int)((x) / PIXEL_SIZE) < mlx_data.map_data.width
					&& mlx_data.map_data.map[(int)((y) / PIXEL_SIZE)][(int)((x)
					/ PIXEL_SIZE)].value == '1')
			break ;
		x += PIXEL_SIZE;
		y += PIXEL_SIZE / tan(grade_to_radian(mlx_data.player.angle + angle));
	}
	p1.xcoord = x;
	p1.ycoord = y;
	return (p1);
}

t_point	ver_2nd_loop(t_mlx_data mlx_data, float x, float y, float angle)
{
	t_point	p1;

	while (1)
	{
		if (x < 0 || y < 0 || x > (mlx_data.map_data.width - 1)
			* PIXEL_SIZE || y > (mlx_data.map_data.heigh) * PIXEL_SIZE
			|| (int)(y / PIXEL_SIZE) - 1 > mlx_data.map_data.heigh
			|| (int)(x / PIXEL_SIZE) > mlx_data.map_data.width)
		{
			x = 3500;
			y = 3300;
			break ;
		}
		else if ((int)((y) / PIXEL_SIZE) < mlx_data.map_data.heigh
			&& (int)((x / PIXEL_SIZE) - 1) < mlx_data.map_data.width
				&& mlx_data.map_data.map[(int)(y / PIXEL_SIZE)][(int)(x /
				PIXEL_SIZE) - 1].value == '1')
			break ;
		x -= PIXEL_SIZE;
		y -= PIXEL_SIZE / tan(grade_to_radian(mlx_data.player.angle + angle));
	}
	p1.xcoord = x;
	p1.ycoord = y;
	return (p1);
}

t_point	check_vertical_steps(t_mlx_data mlx_data, float angle)
{
	t_norm_vars	n;

	n = init_norm_vars();
	if (abs(((int)(mlx_data.player.angle + angle) % 360) <= 180)
		&& abs(((int)(mlx_data.player.angle + angle) % 360) >= 0))
	{
		n.xn = PIXEL_SIZE - (mlx_data.player.position.xcoord - ((int)
					(mlx_data.player.position.xcoord
						/ PIXEL_SIZE) *PIXEL_SIZE));
		n.yn = n.xn / tan(grade_to_radian(mlx_data.player.angle + angle));
		n.x = mlx_data.player.position.xcoord + n.xn;
		n.y = mlx_data.player.position.ycoord + n.yn;
		n.p1 = ver_1st_loop(mlx_data, n.x, n.y, angle);
	}
	else
	{
		n.xn = mlx_data.player.position.xcoord
			- ((int)(mlx_data.player.position.xcoord / PIXEL_SIZE) *PIXEL_SIZE);
		n.yn = n.xn / (float)tan(grade_to_radian(mlx_data.player.angle
					+ angle));
		n.x = mlx_data.player.position.xcoord - n.xn;
		n.y = mlx_data.player.position.ycoord - n.yn;
		n.p1 = ver_2nd_loop(mlx_data, n.x, n.y, angle);
	}
	return (n.p1);
}

int	check_bug_ver(t_mlx_data mlx_data, t_point point)
{
	if ((mlx_data.player.angle % 360) < 250
		&& (mlx_data.player.angle % 360) > 110)
	{
		if (point.ycoord > mlx_data.player.position.ycoord)
			return (1);
		else
			return (0);
	}
	return (0);
}
