/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:30:17 by delvira-          #+#    #+#             */
/*   Updated: 2023/06/09 19:17:35 by delvira-         ###   ########.fr       */
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

t_point    check_horizontal_steps(t_mlx_data mlx_data, float angle)
{
	float	yn;
	float	xn;
	float		x;
	float		y;
	t_point	p1;

	xn = 0;
	yn = 0;
	y = 0;
	x = 0;
	if (abs((int)(mlx_data.player.angle + angle) % 360) <= 270 && abs(((int)(mlx_data.player.angle + angle) % 360) >= 90))
	{
		yn = mlx_data.player.position.ycoord - ((int)(mlx_data.player.position.ycoord / PIXEL_SIZE) *PIXEL_SIZE);
		xn = yn * (float)tan(grade_to_radian(mlx_data.player.angle + angle));
		x = roundf(mlx_data.player.position.xcoord) - xn;
		y = roundf(mlx_data.player.position.ycoord) - yn;
		while (1)
		{
			if (x < 0 || y < 0 ||x > (mlx_data.map_data.width - 1) * PIXEL_SIZE || y > (mlx_data.map_data.heigh - 1) * PIXEL_SIZE || (int)(y / PIXEL_SIZE) - 1 > mlx_data.map_data.heigh || (int)(x / PIXEL_SIZE) > mlx_data.map_data.width)
			{
				x = 3500;
				y = 3300;
				// ft_print_big_dot(mlx_data.img, x, y, get_rgba(255, 255, 0, 255));
				break;
			}
			else if (x > 0 && y > 0 && (int)(y / PIXEL_SIZE) - 1 < mlx_data.map_data.heigh && (int)(x / PIXEL_SIZE) < mlx_data.map_data.width && mlx_data.map_data.map[(int)(y / PIXEL_SIZE) - 1][(int)(x / PIXEL_SIZE)].value == '1')
			{
				// ft_print_big_dot(mlx_data.img, x, y, get_rgba(255, 0, 0, 255));
				// ft_print_big_dot(mlx_data.img, x, y, get_rgba(255, 0, 0, 255));
				break ;
			}
			y -= PIXEL_SIZE;
			x -= PIXEL_SIZE * tan(grade_to_radian(mlx_data.player.angle + angle));
				// ft_print_big_dot(mlx_data.img, x, y, get_rgba(255, 255, 0, 255));
		}
	}
	// else
	// {
	// 	x = 1500;
	// 	y = 300;
	// }
	else if (((int)(mlx_data.player.angle + angle) % 360) >= 270 || ((int)(mlx_data.player.angle + angle) % 360) <= 90)
	{
		yn = PIXEL_SIZE - (mlx_data.player.position.ycoord - ((int)(mlx_data.player.position.ycoord / PIXEL_SIZE) * PIXEL_SIZE));
		xn = yn * (float)tan(grade_to_radian(mlx_data.player.angle + angle));
		x = roundf(mlx_data.player.position.xcoord + xn);
		y = roundf(mlx_data.player.position.ycoord + yn);
		while (1)
		{
			if (x < 0 || y < 0 ||x > (mlx_data.map_data.width - 1) * PIXEL_SIZE || y > (mlx_data.map_data.heigh - 1) * PIXEL_SIZE || (int)(y / PIXEL_SIZE) - 1 > mlx_data.map_data.heigh || (int)(x / PIXEL_SIZE) > mlx_data.map_data.width)
			{
				x = 3500;
				y = 3300;
				// ft_print_big_dot(mlx_data.img, x, y, get_rgba(255, 255, 0, 255));
				break;
			}
			else if (x > 0 && y > 0 && (int)(y / PIXEL_SIZE) - 1 < mlx_data.map_data.heigh && (int)(x / PIXEL_SIZE) < mlx_data.map_data.width && mlx_data.map_data.map[(int)(y / PIXEL_SIZE)][(int)(x / PIXEL_SIZE)].value == '1')
			{
				// ft_print_big_dot(mlx_data.img, x, y, get_rgba(255, 0, 0, 255));
				// ft_print_big_dot(mlx_data.img, x, y, get_rgba(255, 0, 0, 255));
				break ;
			}
			y += PIXEL_SIZE;
			x += PIXEL_SIZE * tan(grade_to_radian(mlx_data.player.angle + angle));
		}
	}
	p1.xcoord = x;
	p1.ycoord = y;
	// printf("angle: %f\n", (int)(mlx_data.player.angle + angle) % 360);
	// printf("x : %f\n", x);
	// printf("y : %f\n", y);
	return (p1);
}

t_point	check_vertical_steps(t_mlx_data mlx_data, float angle)
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
	if (abs(((int)(mlx_data.player.angle + angle) % 360) <= 180) && abs(((int)(mlx_data.player.angle + angle) % 360) >= 0))
	{
		xn = PIXEL_SIZE - (mlx_data.player.position.xcoord - ((int)(mlx_data.player.position.xcoord / PIXEL_SIZE) *PIXEL_SIZE));
		yn = xn / tan(grade_to_radian(mlx_data.player.angle + angle));
		x = roundf(mlx_data.player.position.xcoord) + xn;
		y = roundf(mlx_data.player.position.ycoord) + yn;
		while (1)
		{
			if(x < 0 || y < 0 ||x > (mlx_data.map_data.width - 1) * PIXEL_SIZE || y > (mlx_data.map_data.heigh) * PIXEL_SIZE || (int)(y / PIXEL_SIZE) - 1 > mlx_data.map_data.heigh || (int)(x / PIXEL_SIZE) > mlx_data.map_data.width)
			{
				x = 3500;
				y = 3300;
				// ft_print_big_dot(mlx_data.img, x, y, get_rgba(255, 255, 0, 255));
				break;
			}
			else if (mlx_data.map_data.map[(int)(y / PIXEL_SIZE)][(int)(x / PIXEL_SIZE)].value == '1')
			{
				// ft_print_big_dot(mlx_data.img, x, y, get_rgba(255, 0, 0, 255));
				// ft_print_big_dot(mlx_data.img, x, y, get_rgba(255, 0, 0, 255));
				break ;
			}
			x += PIXEL_SIZE;
			y += PIXEL_SIZE / tan(grade_to_radian(mlx_data.player.angle + angle));
		}
		}
	else if (abs(((int)(mlx_data.player.angle + angle) % 360) >= 180))
	{
		xn = mlx_data.player.position.xcoord - ((int)(mlx_data.player.position.xcoord / PIXEL_SIZE) *PIXEL_SIZE);
		yn = xn / (float)tan(grade_to_radian(mlx_data.player.angle + angle));
		x = mlx_data.player.position.xcoord - xn;
		y = mlx_data.player.position.ycoord - yn;

		while (1)
		{
			if(x < 0 || y < 0 ||x > (mlx_data.map_data.width - 1) * PIXEL_SIZE || y > (mlx_data.map_data.heigh) * PIXEL_SIZE || (int)(y / PIXEL_SIZE) - 1 > mlx_data.map_data.heigh || (int)(x / PIXEL_SIZE) > mlx_data.map_data.width)
			{
				x = 3500;
				y = 3300;
				// ft_print_big_dot(mlx_data.img, x, y, get_rgba(255, 255, 0, 255));
				break;
			}
			else if (mlx_data.map_data.map[(int)(y / PIXEL_SIZE)][(int)(x / PIXEL_SIZE) -1].value == '1')
			{

				break ;
			}
			x -= PIXEL_SIZE;
			y -= PIXEL_SIZE / tan(grade_to_radian(mlx_data.player.angle + angle));
		}
	}
	p1.xcoord = x;
	p1.ycoord = y;
			// ft_print_big_dot(mlx_data.img, x, y, get_rgba(255, 0, 0, 255));
	
	return(p1);
}

t_point	check_distance(t_mlx_data mlx_data, float angle)
{
	t_point	hor;
	t_point	ver;
	double	distancehor;
	double	distancever;

	hor = check_horizontal_steps(mlx_data, angle);
	ver = check_vertical_steps(mlx_data, angle);


	if (hor.xcoord < 0 || hor.ycoord < 0)
		return(ver);
	if (ver.xcoord < 0 || ver.ycoord < 0)
		return(hor);
	distancehor = pow(labs(hor.xcoord - mlx_data.player.position.xcoord), 2) + pow(labs(hor.ycoord - mlx_data.player.position.ycoord), 2);
	distancever = pow(labs(ver.xcoord - mlx_data.player.position.xcoord), 2) + pow(labs(ver.ycoord - mlx_data.player.position.ycoord), 2);
	if (distancehor >= distancever)
	{
		return(ver);
	}
	else if (distancever > distancehor)
	{

		return(hor);
	}
	return (hor);
}

void	put_ray(t_mlx_data mlx_data)
{
	t_point	point1;
	t_point check;
	float	angle;

	angle = -15;


	while (angle <= 15)
	{
		check = check_distance(mlx_data, angle);
		point1.xcoord = (int)check.xcoord;
		point1.ycoord = (int)check.ycoord;
		draw_lines(mlx_data.player.position, point1, mlx_data.img);
		angle += 0.1;
	}
}

