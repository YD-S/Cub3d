/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:30:17 by delvira-          #+#    #+#             */
/*   Updated: 2023/07/26 13:20:08 by delvira-         ###   ########.fr       */
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
			ft_put_pixel(img, x, ycoord, color);
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
	float	x;
	float	y;
	t_point	p1;

	xn = 0;
	yn = 0;
	y = 0;
	x = 0;
	if (abs((int)(mlx_data.player.angle + angle) % 360) <= 270 && abs(((int)(mlx_data.player.angle + angle) % 360) >= 90))
	{
		yn = mlx_data.player.position.ycoord - ((int)(mlx_data.player.position.ycoord / PIXEL_SIZE) *PIXEL_SIZE);
		xn = yn * (float)tan(grade_to_radian(mlx_data.player.angle + angle));
		x = mlx_data.player.position.xcoord - xn;
		y = mlx_data.player.position.ycoord - yn;
		while (1)
		{
			if (x < 0 || y < 0 || x > (mlx_data.map_data.width - 1) * PIXEL_SIZE || y > (mlx_data.map_data.heigh - 1) * PIXEL_SIZE || ((y / PIXEL_SIZE) - 1) > mlx_data.map_data.heigh || (x / PIXEL_SIZE) > mlx_data.map_data.width)
			{
				x = 3500;
				y = 3300;
				break;
			}
			else if (x > 0 && y > 0 && ((y / PIXEL_SIZE) - 1) < mlx_data.map_data.heigh && (x / PIXEL_SIZE) < mlx_data.map_data.width && mlx_data.map_data.map[(int)(y / PIXEL_SIZE) - 1][(int)(x / PIXEL_SIZE)].value == '1')
			{
				break ;
			}
			y -= PIXEL_SIZE;
			x -= PIXEL_SIZE * tan(grade_to_radian(mlx_data.player.angle + angle));
		}
	}
	else if (((int)(mlx_data.player.angle + angle) % 360) > 270 || ((int)(mlx_data.player.angle + angle) % 360) < 90)
	{
		yn = PIXEL_SIZE - (mlx_data.player.position.ycoord - ((int)(mlx_data.player.position.ycoord / PIXEL_SIZE) * PIXEL_SIZE));
		xn = yn * (float)tan(grade_to_radian(mlx_data.player.angle + angle));
		x = mlx_data.player.position.xcoord + xn;
		y = mlx_data.player.position.ycoord + yn;
		while (1)
		{
			if (x < 0 || y < 0 ||x > (mlx_data.map_data.width - 1) * PIXEL_SIZE || y > (mlx_data.map_data.heigh - 1) * PIXEL_SIZE || ((y / PIXEL_SIZE) - 1) > mlx_data.map_data.heigh || (x / PIXEL_SIZE) > mlx_data.map_data.width)
			{
				x = 3500;
				y = 3300;
				break;
			}
			else if (x > 0 && y > 0 && ((y / PIXEL_SIZE) - 1) < mlx_data.map_data.heigh && (x / PIXEL_SIZE) < mlx_data.map_data.width)
			{
				// printf("x: %i\n", (int)((y) / PIXEL_SIZE));
				// printf("y: %i\n", (int)((x + 1) / PIXEL_SIZE));
				if ((mlx_data.player.angle % 360) + angle < 90)
				{
					if (mlx_data.map_data.map[(int)((y) / PIXEL_SIZE)][(int)((x) / PIXEL_SIZE)].value == '1')
						break ;
				}
				else if ((mlx_data.player.angle % 360) + angle >= 90)
				{
					if (mlx_data.map_data.map[(int)((y) / PIXEL_SIZE)][(int)((x) / PIXEL_SIZE)].value == '1')
						break ;
				}
			}
			y += PIXEL_SIZE;
			x += PIXEL_SIZE * tan(grade_to_radian(mlx_data.player.angle + angle));
		}
	}
	p1.xcoord = x;
	p1.ycoord = y;
	
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
		x = mlx_data.player.position.xcoord + xn;
		y = mlx_data.player.position.ycoord + yn;
		while (1)
		{
			if(x < 0 || y < 0 ||x > (mlx_data.map_data.width - 1) * PIXEL_SIZE || y > (mlx_data.map_data.heigh) * PIXEL_SIZE || (int)(y / PIXEL_SIZE) - 1 > mlx_data.map_data.heigh || (int)((x) / PIXEL_SIZE) > mlx_data.map_data.width)
			{
				x = 3500;
				y = 3300;
				// ft_print_big_dot(mlx_data.img, x, y, get_rgba(255, 255, 0, 255));
				break;
			}
			else if ((int)((y) / PIXEL_SIZE) < mlx_data.map_data.heigh && (int)((x) / PIXEL_SIZE) < mlx_data.map_data.width && mlx_data.map_data.map[(int)((y) / PIXEL_SIZE)][(int)((x) / PIXEL_SIZE)].value == '1')
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
			else if ((int)((y) / PIXEL_SIZE) < mlx_data.map_data.heigh && (int)((x / PIXEL_SIZE) - 1) < mlx_data.map_data.width && mlx_data.map_data.map[(int)(y / PIXEL_SIZE)][(int)(x / PIXEL_SIZE) -1].value == '1')
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
int check_bug_hor(t_mlx_data mlx_data, t_point point)
{
	if ((mlx_data.player.angle % 360) < 340 && (mlx_data.player.angle % 360) > 200)
	{
		if (point.xcoord > mlx_data.player.position.xcoord)
			return (1);
		else
			return (0);
	}
	return (0);
}
int check_bug_ver(t_mlx_data mlx_data, t_point point)
{
	if ((mlx_data.player.angle % 360) < 250 && (mlx_data.player.angle % 360) > 110)
	{
		if (point.ycoord > mlx_data.player.position.ycoord)
			return (1);
		else
			return (0);
	}
	return (0);
}

t_point	check_distance(t_mlx_data mlx_data, float angle)
{
	t_point	hor;
	t_point	ver;
	int		distancehor;
	int		distancever;

	hor = check_horizontal_steps(mlx_data, angle);
	ver = check_vertical_steps(mlx_data, angle);
	hor.type = 0;
	ver.type = 1;

	if (hor.xcoord < 0 || hor.ycoord < 0 || check_bug_hor(mlx_data, hor) == 1)
		return(ver);
	if (ver.xcoord < 0 || ver.ycoord < 0 || check_bug_ver(mlx_data, ver) == 1)
		return(hor);
	distancehor = pow(fabsf(hor.xcoord - mlx_data.player.position.xcoord), 2) + pow(fabsf(hor.ycoord - mlx_data.player.position.ycoord), 2);
	distancever = pow(fabsf(ver.xcoord - mlx_data.player.position.xcoord), 2) + pow(fabsf(ver.ycoord - mlx_data.player.position.ycoord), 2);
	if (distancehor >= distancever)
	{
		return(ver);
	}
	else if (distancever > distancehor)
		return(hor);
	return (hor);
}

t_mlx_data	put_ray(t_mlx_data mlx_data)
{
	t_point				point1;
	float				angle;
	int					x;

	angle = -15;
	//angle = 0;
	x = SCREEN_WIDTH;
	while (angle < 15)
	{
		point1 = check_distance(mlx_data, angle);
	//	point1.xcoord = point1.xcoord;
	//	point1.ycoord = point1.ycoord;
		mlx_data.proj_data.ray_array[x].end_point = point1;
		mlx_data.proj_data.ray_array[x].angle = ((int)(mlx_data.player.angle + angle) % 360);
		mlx_data.proj_data.ray_array[x].distance = sqrt(pow(fabsf(point1.xcoord - mlx_data.player.position.xcoord), 2) + pow(fabsf(point1.ycoord - mlx_data.player.position.ycoord), 2));
		draw_lines(mlx_data.player.position, point1, mlx_data.img);
		angle += RAY_DIV;
		x--;
	}
	// printf("distance: %d\n", (int)(mlx_data.proj_data.ray_array[15].distance* 0.01));
	return (mlx_data);
}

char ft_texture(t_mlx_data *mlx_data, int x, int y)
{
	(void)y;
	if(mlx_data->proj_data.ray_array[x].end_point.type == 1 && mlx_data->proj_data.ray_array[x].end_point.xcoord > mlx_data->player.position.xcoord)
		return ('E');
	else if(mlx_data->proj_data.ray_array[x].end_point.type == 1 && mlx_data->proj_data.ray_array[x].end_point.xcoord < mlx_data->player.position.xcoord)
		return ('W');
	else if (mlx_data->proj_data.ray_array[x].end_point.type == 0 && mlx_data->proj_data.ray_array[x].end_point.ycoord < mlx_data->player.position.ycoord)
		return ('N');
	else if (mlx_data->proj_data.ray_array[x].end_point.type == 0 && mlx_data->proj_data.ray_array[x].end_point.ycoord > mlx_data->player.position.ycoord)
		return ('S');
	return ('\0');
}

int getxtex(char tex, int x, t_mlx_data mlx_data)
{
	int ret = 0;
	if(tex =='N')
		return (((((int)mlx_data.proj_data.ray_array[x].end_point.xcoord % PIXEL_SIZE)) * mlx_data.map_data.texture.NO->width) / PIXEL_SIZE);
	else if (tex == 'S')
		return (((( PIXEL_SIZE - (int)mlx_data.proj_data.ray_array[x].end_point.xcoord % PIXEL_SIZE)) * mlx_data.map_data.texture.SO->width) / PIXEL_SIZE);
	else if(tex == 'W')
		return ((((PIXEL_SIZE - (int)mlx_data.proj_data.ray_array[x].end_point.ycoord % PIXEL_SIZE)) * mlx_data.map_data.texture.WE->width) / PIXEL_SIZE);
	else if (tex == 'E')
		return (((((int)mlx_data.proj_data.ray_array[x].end_point.ycoord % PIXEL_SIZE)) * mlx_data.map_data.texture.EA->width) / PIXEL_SIZE);
	return ret;
}

float getstep(int height, t_mlx_data mlx_data, char tex)
{
	float ret = 0;
	if(tex =='N')
		ret = 1.0 * mlx_data.map_data.texture.NO->height / height;
	else if (tex == 'S')
		ret = 1.0 * mlx_data.map_data.texture.SO->height / height;
	else if(tex == 'W')
		ret = 1.0 * mlx_data.map_data.texture.WE->height / height;
	else if (tex == 'E')
		ret = 1.0 * mlx_data.map_data.texture.EA->height / height;
	return (ret);
}

uint32_t reversecolor(unsigned int coloraux)
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

uint32_t gettexcolor(char tex, int x, int y, t_mlx_data mlx_data)
{
	uint32_t color = 0;
	if(tex =='N')
		color = ((unsigned int *)mlx_data.map_data.texture.NO->pixels)[x + y * mlx_data.map_data.texture.NO->width];
	else if (tex == 'S')
		color = ((unsigned int *)mlx_data.map_data.texture.SO->pixels)[x + y * mlx_data.map_data.texture.SO->width];
	else if(tex == 'W')
		color = ((unsigned int *)mlx_data.map_data.texture.WE->pixels)[x + y * mlx_data.map_data.texture.WE->width];
	else if (tex == 'E')
		color = ((unsigned int *)mlx_data.map_data.texture.EA->pixels)[x + y * mlx_data.map_data.texture.EA->width];
	return (reversecolor(color));
}

void	paint_square_td(t_mlx_data mlx_data, int height, int x_start, int color)
{
	(void)color;
	int y = 0;
	char tex;
	int xtex = 0;
	float step = 0;
	y = 0;
	tex = ft_texture(&mlx_data, x_start, (SCREEN_HEIGH / 2) - (height / 2) + y);
	xtex = getxtex(tex, x_start, mlx_data);
	step = getstep(height, mlx_data, tex);
	while (y < height)
	{
		ft_put_pixel(mlx_data.img, x_start, (SCREEN_HEIGH / 2) - (height / 2) + y, gettexcolor(tex, xtex, y*step, mlx_data));
		//ft_put_pixel(mlx_data.img, x_start, (SCREEN_HEIGH / 2) - (height / 2) + y, 0xFFFFFFFF);
		y++;
	}

}

void ft_put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
	if ((x > 0 && x < SCREEN_WIDTH) && (y > 0 && y < SCREEN_HEIGH))
		mlx_put_pixel(img, x , y , color);
}

void	projection(t_mlx_data mlx_data)
{
	int	i;
	int	color;
	int	x_start;
	float	ray_height;
//	int	y;

	i = 0;
	x_start = 0;
	while (i < mlx_data.proj_data.n_rays)
	{
		ray_height = SCREEN_HEIGH / (mlx_data.proj_data.ray_array[i].distance) * WALL_HEIGHT_SCALE;
		mlx_data.proj_data.ray_array[i].ray_heigh = ray_height;
		color = 255 - 255 * (mlx_data.proj_data.ray_array[i].distance / 1000);
	//	y = ((SCREEN_HEIGH / 2) - (ray_height / 2));
		paint_square_td(mlx_data, ray_height, x_start, color);
		i++;
		x_start += 1;
	}
}
