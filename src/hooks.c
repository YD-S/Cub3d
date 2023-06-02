#include "cub3d.h"

void	repaint_map(t_mlx_data *mlx_data)
{
	paint_image_black(*mlx_data);
	paint_map(*mlx_data);
	paint_horizontal_lines(*mlx_data);
	paint_vertical_lines(*mlx_data);
	put_player(*mlx_data);
	put_ray(*mlx_data);
}

void	call_movement_hooks(t_mlx_data *mlx_data, struct mlx_key_data keydata)
{
	if (keydata.key == MLX_KEY_RIGHT)
	{
		mlx_data->player.angle -= grade_to_radian(5);
	}
	if (keydata.key == MLX_KEY_LEFT)
	{
		mlx_data->player.angle += grade_to_radian(5);
	}
	repaint_map(mlx_data);
}

void	hook(struct mlx_key_data keydata, void *param)
{
	t_mlx_data	*mlx_data;

	mlx_data = (t_mlx_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_terminate(mlx_data->mlx);
		exit(0);
	}
	if (keydata.key == MLX_KEY_W)
	{
		mlx_data->player.position.xcoord = roundf(mlx_data->player.position.xcoord
				+ 5 * sin(mlx_data->player.angle));
		mlx_data->player.position.ycoord = roundf(mlx_data->player.position.ycoord
				+ 5 * cos(mlx_data->player.angle));
	}
	if (keydata.key == MLX_KEY_S)
	{
		mlx_data->player.position.xcoord = roundf(mlx_data->player.position.xcoord
				- 5 * sin(mlx_data->player.angle));
		mlx_data->player.position.ycoord = roundf(mlx_data->player.position.ycoord
				- 5 * cos(mlx_data->player.angle));
	}
	if (keydata.key == MLX_KEY_D)
	{
		mlx_data->player.position.xcoord = roundf(mlx_data->player.position.xcoord
				- 5 * sin(mlx_data->player.angle + grade_to_radian(90)));
		mlx_data->player.position.ycoord = roundf(mlx_data->player.position.ycoord
				- 5 * cos(mlx_data->player.angle + grade_to_radian(90)));
	}
	if (keydata.key == MLX_KEY_A)
	{
		mlx_data->player.position.xcoord = roundf(mlx_data->player.position.xcoord
				+ 5 * sin(mlx_data->player.angle + grade_to_radian(90)));
		mlx_data->player.position.ycoord = roundf(mlx_data->player.position.ycoord
				+ 5 * cos(mlx_data->player.angle + grade_to_radian(90)));
	}
	call_movement_hooks(mlx_data, keydata);
}
