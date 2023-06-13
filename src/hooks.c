#include "cub3d.h"

void	repaint_map(t_mlx_data *mlx_data)
{
	paint_image_black(*mlx_data);
	paint_map(*mlx_data);
	paint_horizontal_lines(*mlx_data);
	paint_vertical_lines(*mlx_data);
	put_player(*mlx_data);
	put_ray(*mlx_data);
	projection(*mlx_data);
}

void	call_movement_hooks(t_mlx_data *mlx_data, struct mlx_key_data keydata)
{
	if (keydata.key == MLX_KEY_RIGHT || keydata.action == MLX_PRESS)
	{
		mlx_data->player.angle += 355;
	}
	if (keydata.key == MLX_KEY_LEFT || keydata.action == MLX_PRESS)
	{
		mlx_data->player.angle += 5;
	}
	repaint_map(mlx_data);
}

int	collision(t_mlx_data *data, float x, float y)
{
	x /= PIXEL_SIZE;
	y /= PIXEL_SIZE;
	ft_printf("X: %f\nY: %f\n", x, y);
	return (data->map_data.map[(int)floorf(x)][(int)floorf(y)].value == '1');
}

void	hook(struct mlx_key_data keydata, void *param)
{
	t_mlx_data	*mlx_data;
	t_point		vel;

	mlx_data = (t_mlx_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_terminate(mlx_data->mlx);
		exit(0);
	}
	else if (keydata.key == MLX_KEY_W)
	{
		vel.xcoord = roundf(5 * sin(grade_to_radian(mlx_data->player.angle)));
		vel.ycoord = roundf(5 * cos(grade_to_radian(mlx_data->player.angle)));
	}
	else if (keydata.key == MLX_KEY_S)
	{
		vel.xcoord = roundf(-5 * sin(grade_to_radian(mlx_data->player.angle)));
		vel.ycoord = roundf(-5 * cos(grade_to_radian(mlx_data->player.angle)));
	}
	else if (keydata.key == MLX_KEY_D)
	{
		vel.xcoord = roundf(-5 * sin(grade_to_radian(mlx_data->player.angle
						+ 90)));
		vel.ycoord = roundf(-5 * cos(grade_to_radian(mlx_data->player.angle
						+ 90)));
	}
	else if (keydata.key == MLX_KEY_A)
	{
		vel.xcoord = roundf(5 * sin(grade_to_radian(mlx_data->player.angle
						+ 90)));
		vel.ycoord = roundf(5 * cos(grade_to_radian(mlx_data->player.angle
						+ 90)));
	}
	if (!collision(mlx_data, mlx_data->player.position.xcoord + vel.xcoord,
			mlx_data->player.position.ycoord + vel.ycoord))
	{
		mlx_data->player.position.xcoord += vel.xcoord;
		mlx_data->player.position.ycoord += vel.ycoord;
	}
	call_movement_hooks(mlx_data, keydata);
}
