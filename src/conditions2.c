/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 16:27:31 by delvira-          #+#    #+#             */
/*   Updated: 2023/08/25 16:39:16 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	condition6(t_mlx_data mlx_data, int radius, int x, int y)
{
	return (pow(((mlx_data.player.position.xcoord - PIXEL_SIZE / 2 + x)
				- (mlx_data.player.position.xcoord)), 2)
		+ pow(((mlx_data.player.position.ycoord - PIXEL_SIZE / 2 + y)
				- (mlx_data.player.position.ycoord)), 2) <= pow(radius,
			2));
}

void	paint_circle(int x, int y, int radius, t_mlx_data mlx_data)
{
	float	a;

	a = 0;
	while (a <= M_PI * 2)
	{
		x = cos(a) * radius + mlx_data.player.position.xcoord;
		y = sin(a) * radius + mlx_data.player.position.ycoord;
		ft_put_pixel(mlx_data.img, x, y, get_rgba(0, 0, 0, 255));
		a += 0.01;
	}
}
