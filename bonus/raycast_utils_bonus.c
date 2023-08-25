/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 19:33:13 by delvira-          #+#    #+#             */
/*   Updated: 2023/08/24 20:07:00 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_norm_vars	init_norm_vars(void)
{
	t_norm_vars	n;

	n.yn = 0;
	n.xn = 0;
	n.x = 0;
	n.y = 0;
	return (n);
}

int	radian_to_angle(float radian)
{
	float	angle;

	angle = fabsf(radian) * (180 / M_PI);
	return (angle);
}

void	ft_put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
	if ((x > 0 && x < SCREEN_WIDTH) && (y > 0 && y < SCREEN_HEIGH))
		mlx_put_pixel(img, x, y, color);
}
