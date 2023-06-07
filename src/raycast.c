/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:30:17 by delvira-          #+#    #+#             */
/*   Updated: 2023/06/07 16:20:01 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_print_big_dot(mlx_image_t *img, float xcoord, float ycoord, uint32_t color)
{
	int	row;
	int	col;
	int	xinit;
	int	x;

	xinit = xcoord;
	col = 0;
	row = 0;
	while (row < 3)
	{
		col = 0;
		x = xinit;
		while (col < 3)
		{
			mlx_put_pixel(img, x, ycoord, color);
			col++;
			x++;
		}
		row++;
		ycoord++;
	}
	return ;
}

int	radian_to_angle(float radian)
{
	float	angle;

	angle = fabsf(radian) * (180 / M_PI);
	return (angle);
}

t_point    check_horizontal_steps(t_mlx_data mlx_data)
{
	float	yn;
	float	xn;
	float	x;
	float	y;
	t_point	p1;

	xn = 0;
	yn = 0;

	if (abs(mlx_data.player.angle % 360) < 270 && abs((mlx_data.player.angle % 360) > 90))
	{
		yn = mlx_data.player.position.ycoord - ((int)(mlx_data.player.position.ycoord / PIXEL_SIZE) *PIXEL_SIZE);
		xn = yn * (float)tan(grade_to_radian(mlx_data.player.angle));
		// ft_print_big_dot(mlx_data.img, roundf(mlx_data.player.position.xcoord) - xn, roundf(mlx_data.player.position.ycoord) - yn, get_rgba(255, 0, 0, 255));
		x = roundf(mlx_data.player.position.xcoord) - xn;
		y = roundf(mlx_data.player.position.ycoord) - yn;
		while (((int)(y / PIXEL_SIZE) < mlx_data.map_data.heigh - 1 && (int)(x / PIXEL_SIZE) < mlx_data.map_data.width - 1 && (int)(y / PIXEL_SIZE) - 1 > 0 && (int)(x / PIXEL_SIZE) - 1 > 0) && mlx_data.map_data.map[(int)(y / PIXEL_SIZE) - 1][(int)(x / PIXEL_SIZE)].value != '1')
		{
			y -= PIXEL_SIZE;
			x -= PIXEL_SIZE * tan(grade_to_radian(mlx_data.player.angle));
			// ft_print_big_dot(mlx_data.img, x, y, get_rgba(255, 0, 0, 255));
		}
	}
	else if ((mlx_data.player.angle % 360) > 270 || (mlx_data.player.angle % 360) < 90)
	{
		yn = PIXEL_SIZE - (mlx_data.player.position.ycoord - ((int)(mlx_data.player.position.ycoord / PIXEL_SIZE) * PIXEL_SIZE));
		xn = yn * (float)tan(grade_to_radian(mlx_data.player.angle));
		x = roundf(mlx_data.player.position.xcoord + xn);
		y = roundf(mlx_data.player.position.ycoord + yn);
		while (((int)(y / PIXEL_SIZE) < mlx_data.map_data.heigh - 1 && (int)(x / PIXEL_SIZE) < mlx_data.map_data.width - 1 && (int)(y / PIXEL_SIZE) - 1 > 0 && (int)(x / PIXEL_SIZE) - 1 > 0) && mlx_data.map_data.map[(int)(y / PIXEL_SIZE)][(int)(x / PIXEL_SIZE)].value != '1')
		{
			y += PIXEL_SIZE;
			x += PIXEL_SIZE * tan(grade_to_radian(mlx_data.player.angle));
			// ft_print_big_dot(mlx_data.img, x, y, get_rgba(255, 0, 0, 255));
		}
	}
	p1.xcoord = x;
	p1.ycoord = y;
	// ft_print_big_dot(mlx_data.img, x, y, get_rgba(255, 255, 0, 255));
	return (p1);
}

t_point	check_vertical_steps(t_mlx_data mlx_data)
{
	float	xn;
	float	yn;
	float	x;
	float	y;
	t_point	p1;

	xn = 0;
	yn = 0;
	x = 0;
	y = 0;
	if (abs(((mlx_data.player.angle) % 360) < 180) && abs(((mlx_data.player.angle) % 360) > 0))
	{
		xn = PIXEL_SIZE - (mlx_data.player.position.xcoord - ((int)(mlx_data.player.position.xcoord / PIXEL_SIZE) *PIXEL_SIZE));
		yn = xn / tan(grade_to_radian(mlx_data.player.angle));
		x = roundf(mlx_data.player.position.xcoord) + xn;
		y = roundf(mlx_data.player.position.ycoord) + yn;
		while ((int)(y / PIXEL_SIZE) > 0 && (int)(x / PIXEL_SIZE) > 0 && (int)(y / PIXEL_SIZE) < mlx_data.map_data.heigh && (int)(x / PIXEL_SIZE) < mlx_data.map_data.width && y > 0 && x > 0 && mlx_data.map_data.map[(int)(y / PIXEL_SIZE)][(int)(x / PIXEL_SIZE)].value != '1' && (int)(y / PIXEL_SIZE) > 0)
		{
			// printf("y: %f\n",y);
			// ft_print_big_dot(mlx_data.img, x, y, get_rgba(255, 0, 0, 255));
			x += PIXEL_SIZE;
			y += PIXEL_SIZE / tan(grade_to_radian(mlx_data.player.angle % 360));
			// printf("tan: %f\n",tan(grade_to_radian(mlx_data.player.angle)));
			// printf("angle: %d\n",mlx_data.player.angle % 360);
		}
		// printf("x: %f\n",x);
		// printf("y: %f\n",y);
		// ft_print_big_dot(mlx_data.img, x, y, get_rgba(255, 0, 0, 255));
		}
	else if (abs(((mlx_data.player.angle) % 360) > 180))
	{
		xn = mlx_data.player.position.xcoord - ((int)(mlx_data.player.position.xcoord / PIXEL_SIZE) *PIXEL_SIZE);
		yn = xn / (float)tan(grade_to_radian(mlx_data.player.angle));
		x = mlx_data.player.position.xcoord - xn;
		y = mlx_data.player.position.ycoord - yn;

		while ((int)(y / PIXEL_SIZE) > 0 && (int)(x / PIXEL_SIZE) > 0 && (int)(y / PIXEL_SIZE) < mlx_data.map_data.heigh && (int)(x / PIXEL_SIZE) < mlx_data.map_data.width && y > 0 && x > 0 && mlx_data.map_data.map[(int)(y / PIXEL_SIZE)][(int)(x / PIXEL_SIZE) -1].value != '1' && (int)(y / PIXEL_SIZE) > 0)
		{
			x -= PIXEL_SIZE;
			y -= PIXEL_SIZE / tan(grade_to_radian(mlx_data.player.angle % 360));
		}
	}
	p1.xcoord = x;
	p1.ycoord = y;
			// ft_print_big_dot(mlx_data.img, x, y, get_rgba(255, 0, 0, 255));
	
	return(p1);
}

t_point	check_distance(t_mlx_data mlx_data)
{
	t_point	hor;
	t_point	ver;
	double	distancehor;
	double	distancever;
	t_point	return_point;

	hor = check_horizontal_steps(mlx_data);
	ver = check_vertical_steps(mlx_data);
	// if (hor.xcoord < 0 || hor.ycoord < 0)
	// 	return(ver);
	// if (ver.xcoord < 0 || ver.ycoord < 0)
	// 	return(hor);
	distancehor = pow(abs(hor.xcoord - mlx_data.player.position.xcoord), 2) + pow(abs(hor.ycoord - mlx_data.player.position.ycoord), 2);
	distancever = pow(abs(ver.xcoord - mlx_data.player.position.xcoord), 2) + pow(abs(ver.ycoord - mlx_data.player.position.ycoord), 2);
	if (distancehor >= distancever)
		return(ver);
	if (distancever > distancehor)
		return(hor);
}

void	put_ray(t_mlx_data mlx_data)
{
	t_point	point1;
	t_point check;

	point1.xcoord = roundf(mlx_data.player.position.xcoord + 50
			* sin(grade_to_radian(mlx_data.player.angle)));
	point1.ycoord = roundf(mlx_data.player.position.ycoord + 50
			* cos(grade_to_radian(mlx_data.player.angle)));
	// ft_print_big_dot(mlx_data.img, point1.xcoord, point1.ycoord, get_rgba(255, 0, 0, 255));
	// draw_lines(mlx_data.player.position, point1, mlx_data.img);
	point1 = check_distance(mlx_data);
	check.xcoord = (int) point1.xcoord;
	check.ycoord = (int) point1.ycoord;
	// ft_print_big_dot(mlx_data.img, check.xcoord, check.ycoord, get_rgba(255, 0, 0, 255));
	draw_lines(mlx_data.player.position, check, mlx_data.img);
	// check_horizontal_steps(mlx_data);
	// check_vertical_steps(mlx_data);
}

