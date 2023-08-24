/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 19:56:03 by delvira-          #+#    #+#             */
/*   Updated: 2023/08/24 19:59:44 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*repaint_map(void *param)
{
	t_mlx_data	*mlx_data;

	mlx_data = (t_mlx_data *)param;
	paint_image_black(*mlx_data);
	projection(*mlx_data);
	//paint_map(*mlx_data);
	//paint_horizontal_lines(*mlx_data);
	//paint_vertical_lines(*mlx_data);
	//put_player(*mlx_data);
	put_ray(*mlx_data);
	return (0);
}

void	call_movement_hooks(t_mlx_data *mlx_data, struct mlx_key_data keydata)
{
	if (keydata.key == MLX_KEY_RIGHT || keydata.action == MLX_PRESS)
		mlx_data->player.angle += 355;
	if (keydata.key == MLX_KEY_LEFT || keydata.action == MLX_PRESS)
		mlx_data->player.angle += 5;
}

int	collision(t_mlx_data *data, float x, float y)
{
	x /= PIXEL_SIZE;
	y /= PIXEL_SIZE;
	return (data->map_data.map[(int)floorf(y)][(int)floorf(x)].value == '1');
}

float	get_xcord(t_mlx_data mlx_data, t_point vel)
{
	if (mlx_data.player.angle % 360 <= 180)
		return (mlx_data.player.position.xcoord + vel.xcoord);
	else
		return (mlx_data.player.position.xcoord - vel.xcoord);
}

float	get_ycord(t_mlx_data mlx_data, t_point vel)
{
	if (mlx_data.player.angle % 360 >= 90 && mlx_data.player.angle % 360 <= 270)
		return (mlx_data.player.position.ycoord + vel.ycoord);
	else
		return (mlx_data.player.position.ycoord - vel.ycoord);
}
