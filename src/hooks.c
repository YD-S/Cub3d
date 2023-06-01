
#include "cub3d.h"

void repaint_map(t_mlx_data *mlx_data)
{
    paint_image_black(*mlx_data);
	paint_map(*mlx_data);
	paint_horizontal_lines(*mlx_data);
	paint_vertical_lines(*mlx_data);
	put_player(*mlx_data);
    ft_printf("HOLAAAA");
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
		mlx_data->player.position.ycoord -= 5;
	}
	if (keydata.key == MLX_KEY_S)
	{
		mlx_data->player.position.ycoord += 5;
	}
	if (keydata.key == MLX_KEY_D)
	{
		mlx_data->player.position.xcoord += 5;
	}
	if (keydata.key == MLX_KEY_A)
	{
		mlx_data->player.position.xcoord -= 5;
	}
	repaint_map(mlx_data);
}
