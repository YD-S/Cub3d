/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_horizontal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 19:39:24 by delvira-          #+#    #+#             */
/*   Updated: 2023/08/24 19:55:05 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point	horiz_1st_loop(t_mlx_data mlx_data, float x, float y, float angle)
{
	t_point	p1;

	while (1)
	{
		if (x < 0 || y < 0 || x > (mlx_data.map_data.width - 1) * PIXEL_SIZE
			|| y > (mlx_data.map_data.heigh - 1) * PIXEL_SIZE || ((y
					/ PIXEL_SIZE) - 1) > mlx_data.map_data.heigh
			|| (x / PIXEL_SIZE) > mlx_data.map_data.width)
		{
			x = 3500;
			y = 3300;
			break ;
		}
		else if (x > 0 && y > 0 && ((y / PIXEL_SIZE) - 1)
			< mlx_data.map_data.heigh && (x / PIXEL_SIZE)
			< mlx_data.map_data.width
			&& mlx_data.map_data.map[(int)(y / PIXEL_SIZE)
			- 1][(int)(x / PIXEL_SIZE)].value == '1')
			break ;
		y -= PIXEL_SIZE;
		x -= PIXEL_SIZE * tan(grade_to_radian(mlx_data.player.angle + angle));
	}
	p1.xcoord = x;
	p1.ycoord = y;
	return (p1);
}

t_point	horiz_2nd_loop(t_mlx_data mlx_data, float x, float y, float angle)
{
	t_point	p1;

	while (1)
	{
		if (condition5(mlx_data, x, y))
		{
			x = 3500;
			y = 3300;
			break ;
		}
		else if (x > 0 && y > 0 && ((y / PIXEL_SIZE) - 1)
			< mlx_data.map_data.heigh
			&& (x / PIXEL_SIZE) < mlx_data.map_data.width)
		{
			if (condition3(mlx_data, x, y, angle))
				break ;
			else if (condition4(mlx_data, x, y, angle))
				break ;
		}
		y += PIXEL_SIZE;
		x += PIXEL_SIZE * tan(grade_to_radian(mlx_data.player.angle + angle));
	}
	p1.xcoord = x;
	p1.ycoord = y;
	return (p1);
}

t_point	check_horizontal_steps(t_mlx_data mlx_data, float angle)
{
	t_norm_vars	n;

	n = init_norm_vars();
	if (condition2(mlx_data, angle))
	{
		n.yn = mlx_data.player.position.ycoord - ((int)
				(mlx_data.player.position.ycoord / PIXEL_SIZE) *PIXEL_SIZE);
		n.xn = n.yn * (float)tan(grade_to_radian(mlx_data.player.angle
					+ angle));
		n.x = mlx_data.player.position.xcoord - n.xn;
		n.y = mlx_data.player.position.ycoord - n.yn;
		n.p1 = horiz_1st_loop(mlx_data, n.x, n.y, angle);
	}
	else
	{
		n.yn = PIXEL_SIZE - (mlx_data.player.position.ycoord
				- ((int)(mlx_data.player.position.ycoord
						/ PIXEL_SIZE) *PIXEL_SIZE));
		n.xn = n.yn *(float)tan(grade_to_radian(mlx_data.player.angle
					+ angle));
		n.x = mlx_data.player.position.xcoord + n.xn;
		n.y = mlx_data.player.position.ycoord + n.yn;
		n.p1 = horiz_2nd_loop(mlx_data, n.x, n.y, angle);
	}
	return (n.p1);
}

int	check_bug_hor(t_mlx_data mlx_data, t_point point)
{
	if ((mlx_data.player.angle % 360) < 340
		&& (mlx_data.player.angle % 360) > 200)
	{
		if (point.xcoord > mlx_data.player.position.xcoord)
			return (1);
		else
			return (0);
	}
	return (0);
}
