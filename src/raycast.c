/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:30:17 by delvira-          #+#    #+#             */
/*   Updated: 2023/06/05 20:09:09 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	radian_to_angle(float radian)
{
	float	angle;

	angle = abs(radian) * (180 / M_PI);
	return (angle);
}

void    check_horizontal_steps(t_mlx_data mlx_data)
{
	float	yn;
	float	xn;

	xn = 0;
	yn = 0;
	if (abs(((mlx_data.player.angle) % 360) == 270) || abs(((mlx_data.player.angle) % 360) == 90))
	{
		
	}
	else if (abs(mlx_data.player.angle % 360) < 270 && abs((mlx_data.player.angle % 360) > 90))
	{
		yn = mlx_data.player.position.ycoord - ((int)(mlx_data.player.position.ycoord / PIXEL_SIZE) *PIXEL_SIZE);
		xn = yn * (float)tan(grade_to_radian(mlx_data.player.angle));
		mlx_put_pixel(mlx_data.img, mlx_data.player.position.xcoord - xn, mlx_data.player.position.ycoord - yn, get_rgba(255, 0, 0, 255));
	}
	else if ((mlx_data.player.angle % 360) > 270 || (mlx_data.player.angle % 360) < 90)
	{
		yn = mlx_data.player.position.ycoord - ((int)(mlx_data.player.position.ycoord / PIXEL_SIZE) * PIXEL_SIZE);
		xn = yn * (float)tan(grade_to_radian(mlx_data.player.angle));
		mlx_put_pixel(mlx_data.img, mlx_data.player.position.xcoord + xn, mlx_data.player.position.ycoord + yn, get_rgba(255, 0, 0, 255));
	}
}

void	check_vertical_steps(t_mlx_data mlx_data)
{
	float	xn;
	float	yn;

	if (abs(((mlx_data.player.angle) % 360) == 180) || abs(((mlx_data.player.angle) % 360) == 0))
	{
		
	}
	else if (abs(((mlx_data.player.angle) % 360) < 180))
	{
		xn = mlx_data.player.position.xcoord - ((int)(mlx_data.player.position.xcoord / PIXEL_SIZE) *PIXEL_SIZE);
		yn = xn / (float)tan(grade_to_radian(mlx_data.player.angle));
		mlx_put_pixel(mlx_data.img, mlx_data.player.position.xcoord + xn, mlx_data.player.position.ycoord + yn, get_rgba(255, 0, 0, 255));
	}
	else if (abs(((mlx_data.player.angle) % 360) > 180))
	{
		xn = mlx_data.player.position.xcoord - ((int)(mlx_data.player.position.xcoord / PIXEL_SIZE) *PIXEL_SIZE);
		yn = xn / (float)tan(grade_to_radian(mlx_data.player.angle));
		mlx_put_pixel(mlx_data.img, mlx_data.player.position.xcoord - xn, mlx_data.player.position.ycoord - yn, get_rgba(255, 0, 0, 255));

	}
}

void	put_ray(t_mlx_data mlx_data)
{
	t_point	point1;

	point1.xcoord = roundf(mlx_data.player.position.xcoord + 50
			* sin(grade_to_radian(mlx_data.player.angle)));
	point1.ycoord = roundf(mlx_data.player.position.ycoord + 50
			* cos(grade_to_radian(mlx_data.player.angle)));
	draw_lines(mlx_data.player.position, point1, mlx_data.img);
	check_horizontal_steps(mlx_data);
	check_vertical_steps(mlx_data);
}

