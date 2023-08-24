/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:30:17 by delvira-          #+#    #+#             */
/*   Updated: 2023/08/24 20:06:13 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		return (ver);
	if (ver.xcoord < 0 || ver.ycoord < 0 || check_bug_ver(mlx_data, ver) == 1)
		return (hor);
	distancehor = pow(fabsf(hor.xcoord - mlx_data.player.position.xcoord), 2)
		+ pow(fabsf(hor.ycoord - mlx_data.player.position.ycoord), 2);
	distancever = pow(fabsf(ver.xcoord - mlx_data.player.position.xcoord), 2)
		+ pow(fabsf(ver.ycoord - mlx_data.player.position.ycoord), 2);
	if (distancehor >= distancever)
		return (ver);
	else if (distancever > distancehor)
		return (hor);
	return (hor);
}

t_mlx_data	put_ray(t_mlx_data mlx_data)
{
	t_point				point1;
	float				angle;
	int					x;

	angle = -15;
	x = SCREEN_WIDTH;
	while (angle < 15)
	{
		point1 = check_distance(mlx_data, angle);
		mlx_data.proj_data.ray_array[x].end_point = point1;
		mlx_data.proj_data.ray_array[x].angle
			= ((int)(mlx_data.player.angle + angle) % 360);
		mlx_data.proj_data.ray_array[x].distance
			= sqrt(pow(fabsf(point1.xcoord - mlx_data.player.position.xcoord),
					2)
				+ pow(fabsf(point1.ycoord - mlx_data.player.position.ycoord),
					2));
		angle += RAY_DIV;
		x--;
	}
	return (mlx_data);
}

char	ft_texture(t_mlx_data *mlx_data, int x, int y)
{
	(void)y;
	if (mlx_data->proj_data.ray_array[x].end_point.type == 1
		&& mlx_data->proj_data.ray_array[x].end_point.xcoord
		> mlx_data->player.position.xcoord)
		return ('E');
	else if (mlx_data->proj_data.ray_array[x].end_point.type == 1
		&& mlx_data->proj_data.ray_array[x].end_point.xcoord
		< mlx_data->player.position.xcoord)
		return ('W');
	else if (mlx_data->proj_data.ray_array[x].end_point.type == 0
		&& mlx_data->proj_data.ray_array[x].end_point.ycoord
		< mlx_data->player.position.ycoord)
		return ('N');
	else if (mlx_data->proj_data.ray_array[x].end_point.type == 0
		&& mlx_data->proj_data.ray_array[x].end_point.ycoord
		> mlx_data->player.position.ycoord)
		return ('S');
	return ('\0');
}

int	getxtex(char tex, int x, t_mlx_data mlx_data)
{
	int	ret;

	ret = 0;
	if (tex == 'N')
		return (((int)mlx_data.proj_data.ray_array[x].end_point.xcoord
				% PIXEL_SIZE)
			* mlx_data.map_data.texture.no->width / PIXEL_SIZE);
	else if (tex == 'S')
		return ((((PIXEL_SIZE
						- (int)
						mlx_data.proj_data.ray_array[x].end_point.xcoord
						% PIXEL_SIZE))
				* mlx_data.map_data.texture.so->width) / PIXEL_SIZE);
	else if (tex == 'W')
		return ((((PIXEL_SIZE
						- (int)
						mlx_data.proj_data.ray_array[x].end_point.ycoord
						% PIXEL_SIZE))
				* mlx_data.map_data.texture.we->width) / PIXEL_SIZE);
	else if (tex == 'E')
		return ((((int)mlx_data.proj_data.ray_array[x].end_point.ycoord
					% PIXEL_SIZE)
				* mlx_data.map_data.texture.ea->width) / PIXEL_SIZE);
	return (ret);
}

float	getstep(int height, t_mlx_data mlx_data, char tex)
{
	float	ret;

	ret = 0;
	if (tex == 'N')
		ret = 1.0 * mlx_data.map_data.texture.no->height / height;
	else if (tex == 'S')
		ret = 1.0 * mlx_data.map_data.texture.so->height / height;
	else if (tex == 'W')
		ret = 1.0 * mlx_data.map_data.texture.we->height / height;
	else if (tex == 'E')
		ret = 1.0 * mlx_data.map_data.texture.ea->height / height;
	return (ret);
}
